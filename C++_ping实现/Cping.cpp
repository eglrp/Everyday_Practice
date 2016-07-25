
#include "Cping.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define ICMP_ECHO 8  // ������Ա��Ĵ���
#define ICMP_ECHOREPLY 0
#define ICMP_MIN 8  // ��С8�ֽ�ICMP��
#define MAX_ICMP_PACKET 1024 // ���ICMP��С


#pragma pack(4)
// IPͷ�ײ��ṹ
struct IpHeader
{
	unsigned int h_len : 4;   // �ײ�����
	unsigned int version : 4;   // IP�汾
	unsigned char tos;    // ��������
	unsigned short total_len;  // ���ܳ���
	unsigned short ident;   // ��ʶ��
	unsigned short frag_and_flags; // ��־
	unsigned char ttl;    // ��������
	unsigned char proto;   // protocol (TCP, UDP etc) Э������
	unsigned short checksum;  // IP�����
	unsigned int sourceIP;   // Դ��ַIP
	unsigned int destIP;   // Ŀ�ĵ�ַIP
};
// ICMP �ײ��ṹ
struct IcmpHeader
{
	BYTE i_type; // ����
	BYTE i_code; // ��������
	USHORT i_cksum; // �����
	USHORT i_id; // ��ַ
	USHORT i_seq; // ����˳��
	// ����һ��ʱ���
	ULONG timestamp;
};
CPing::CPing(void)
{
	m_socketRaw = INVALID_SOCKET;
	m_bPrintInfo = false;
	Init();
}

CPing::~CPing(void)
{
	FInit();
}
bool CPing::Init()
{
	WSADATA wsaData = { 0 };
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
		return false;
	//���������׽���
	// ע��Ϊ��ʹ�÷��ͽ��ճ�ʱ����(������SO_RCVTIMEO, SO_SNDTIMEO)��
	// ���뽫��־λ��ΪWSA_FLAG_OVERLAPPED !
	m_socketRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_socketRaw == INVALID_SOCKET)
		return false;

	// ����һ���н���ʱ�޵��׽���
	int nTimeout = 1000;
	int nResult = setsockopt(m_socketRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeout, sizeof(nTimeout));
	if (nResult == SOCKET_ERROR)
		return false;
	//����һ���з���ʱ�޵��׽���
	nTimeout = 1000;
	nResult = setsockopt(m_socketRaw, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeout, sizeof(nTimeout));
	if (nResult == SOCKET_ERROR)
		return false;

	return true;
}
bool CPing::FInit()
{
	WSACleanup();
	return true;
}
bool CPing::PingHelper(const char* pDscAddr, int nPackNum, int nDataSize)
{
	if (pDscAddr == NULL || nPackNum <= 0)
		return false;

	// ������������
	sockaddr_in addrDsc = { 0 };
	hostent* pHostent = gethostbyaddr(pDscAddr, strlen(pDscAddr), AF_INET);
	if (pHostent != NULL)
	{
		addrDsc.sin_family = AF_INET;
		addrDsc.sin_addr.S_un.S_addr = inet_addr(pDscAddr);
	}
	else
	{
		pHostent = gethostbyname(pDscAddr);
		if (pHostent == NULL)
			return false;
		addrDsc.sin_family = pHostent->h_addrtype;
		memcpy(&(addrDsc.sin_addr), pHostent->h_addr, pHostent->h_length);
	}
	if (m_bPrintInfo)
	{
		std::cout << "Pinging " << inet_ntoa(addrDsc.sin_addr);
		std::cout << " with " << nDataSize << " bytes of data:" << std::endl << std::endl;
	}

	char szIcmpData[MAX_ICMP_PACKET] = { 0 };
	char szRecvBuff[MAX_ICMP_PACKET] = { 0 };
	ConstructIcmpMessage(szIcmpData, nDataSize);
	IcmpHeader* pIcmpHeader = reinterpret_cast<IcmpHeader*>(szIcmpData);
	int nPackSize = nDataSize + sizeof(IcmpHeader);
	int nSeqNO = 0;
	int nRet = 0;
	sockaddr_in addrSrc = { 0 };
	int nRecvPacket = 0;
	for (int i = 0; i < nPackNum; ++i)
	{
		pIcmpHeader->i_cksum = 0; // �Ȱ�ICMP�ļ��������
		pIcmpHeader->i_seq = nSeqNO++; // ����˳���һ
		pIcmpHeader->timestamp = GetTickCount(); // ��¼ʱ��
		pIcmpHeader->i_cksum = CheckSum((USHORT*)szIcmpData, nPackSize);// ��������
		nRet = sendto(m_socketRaw, szIcmpData, nPackSize, 0, (sockaddr*)&addrDsc, sizeof(addrDsc));
		if (nRet == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT) // ���ͳ�ʱ
			{
				if (m_bPrintInfo)
				{
					std::cout << "Request timed out." << std::endl;
				}
				continue;
			}
			return false;
		}
		int nSrcLen = sizeof(addrSrc);
		nRet = recvfrom(m_socketRaw, szRecvBuff, sizeof(szRecvBuff), 0, (sockaddr*)&addrSrc, &nSrcLen);
		if (nRet == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT) // ���ճ�ʱ
			{
				if (m_bPrintInfo)
				{
					std::cout << "Request timed out." << std::endl;
				}
				continue;
			}
			return false;
		}
		if (DecodeIpPacket(szRecvBuff, nRet, &addrSrc))
			++nRecvPacket;
		if (m_bPrintInfo)
			Sleep(1000);
	}
	if (m_bPrintInfo)
	{
		std::cout << std::endl << "Packets: Sent = " << nPackNum;
		std::cout << ", Received = " << nRecvPacket;
		std::cout << ", Lost = " << nPackNum - nRecvPacket;
		std::cout << " (" << (nPackNum - nRecvPacket) * 100 / nPackNum;
		std::cout << "% loss)" << std::endl;
	}

	return nRecvPacket > 0;
}
bool CPing::ConstructIcmpMessage(char* pDataBuff, int nDataSize)
{
	if (pDataBuff == NULL)
		return false;
	IcmpHeader* pIcmpHeader = (IcmpHeader*)pDataBuff;
	pIcmpHeader->i_type = ICMP_ECHO;     // ���û��Ա���
	pIcmpHeader->i_code = 0;
	pIcmpHeader->i_id = (USHORT)GetCurrentProcessId();// ��ȡ��ǰ����ID
	pIcmpHeader->i_cksum = 0;       // ��ʼ�������Ϊ0
	pIcmpHeader->i_seq = 0;       // ˳���
	char* pDataPart = pDataBuff + sizeof(IcmpHeader);  // ������������ַ
	memset(pDataPart, 'E', nDataSize);      // ����������ʼ��
	return true;
}
// ����У���
USHORT CPing::CheckSum(USHORT* pBuff, int nSize)
{
	unsigned long ulChkSum = 0; // ���������0
	while (nSize > 1)
	{
		ulChkSum += *pBuff++; // ������IP���ݱ������ݶ��ӵ�һ��
		nSize -= sizeof(USHORT);// ÿ�μ�������ʮ��λ�����ƺ� ��ÿ�μ������ֽڣ�
	}
	if (nSize != 0)
	{
		ulChkSum += *(UCHAR*)pBuff; // �жϵ�ֻʣ��һ���ֽ�û�мӵ������ʱ���������
	}
	ulChkSum = (ulChkSum >> 16) + (ulChkSum & 0XFFFF); // �Ȱ�32bit��������ƺ͵õ�cksum��Ȼ��Ѹ�λ��λ���
	//�õ�16bit�ĺ͡�
	ulChkSum += (ulChkSum >> 16); // �Ѹ�16λ�͵�16λ�������Ľ�λ�ټӵ�У�����
	return (USHORT)(~ulChkSum);  // ȡ���õ������
}
bool CPing::DecodeIpPacket(char* pBuff, int nBuffSize, sockaddr_in* pAddr)
{
	if (pBuff == NULL || nBuffSize <= 0)
		return false;
	IpHeader* pIpHeader = (IpHeader*)pBuff;
	unsigned short usIpHeaderLen = (pIpHeader->h_len) * 4; //����IP�ײ��ĳ���
	IcmpHeader* pIcmpHeader = (IcmpHeader*)(pBuff + usIpHeaderLen);
	//�ж��Ƿ��ǻ���Ӧ����
	if (pIcmpHeader->i_type != ICMP_ECHOREPLY)
		return false;
	// �ж��Ƿ��ǵ�ǰ���̵�IP��ַ��ȷ���Ǵ˴εĻ��Ա��ġ�
	if (pIcmpHeader->i_id != (USHORT)GetCurrentProcessId())
		return false;
	if (nBuffSize < usIpHeaderLen + ICMP_MIN)
		return false;
	if (m_bPrintInfo)
	{
		std::cout << "Reply from " << inet_ntoa(pAddr->sin_addr);
		std::cout << ": bytes=" << nBuffSize - usIpHeaderLen - ICMP_MIN;
		std::cout << " time=" << GetTickCount() - pIcmpHeader->timestamp;
		std::cout << "ms TTL=" << pIpHeader->ttl << std::endl;
	}
	return true;
}
bool CPing::CanPing(const char* pDscAddr)
{
	m_bPrintInfo = false;
	return PingHelper(pDscAddr);
}
void CPing::Ping(const char* pDscAddr, int nPackNum, int nPackSize)
{
	m_bPrintInfo = true;
	PingHelper(pDscAddr, nPackNum, nPackSize);
}

//ʹ�ô���ʾ����
//CPing ping;
//ping.Ping("www.baidu.com");