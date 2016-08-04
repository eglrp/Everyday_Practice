
//#pragma comment (lib,"ws2_32.lib")
//#include <Winsock2.h>
//#include <stdio.h>


//////udp Server
//void main()
//{
//	//�汾Э��
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//	wVersionRequested = MAKEWORD(1, 1);
//	err = WSAStartup(wVersionRequested, &wsaData);
//	if (err != 0) {
//		/* Tell the user that we could not find a usable */
//		/* WinSock DLL.                                  */
//		return;
//	}
//	/* Confirm that the WinSock DLL supports 2.2.*/
//	/* Note that if the DLL supports versions greater    */
//	/* than 2.2 in addition to 2.2, it will still return */
//	/* 2.2 in wVersion since that is the version we      */
//	/* requested.                                        */
//	if (LOBYTE(wsaData.wVersion) != 1 ||
//		HIBYTE(wsaData.wVersion) != 1) {
//		/* Tell the user that we could not find a usable */
//		/* WinSock DLL.                                  */
//		WSACleanup();
//		return;
//	}
//	/* The WinSock DLL is acceptable. Proceed. */
//	//�������ݱ��׽���
//	SOCKET svr = socket(AF_INET, SOCK_DGRAM, 0);
//	//�������ص�ַ��Ϣ
//	SOCKADDR_IN addr;
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(6000);
//	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	int len = sizeof(sockaddr);
//	bind(svr, (sockaddr*)&addr, len);
//	//�����ͻ��˵�ַ����
//	SOCKADDR_IN addrClient;
//	char recvBuf[128];
//	char sendBuf[128];
//	char tempBuf[256];
//	while (true)
//	{
//		//��������
//		printf("wait receive client message :\n");
//		recvfrom(svr, recvBuf, 128, 0, (sockaddr*)&addrClient, &len);
//		char* ipClient = inet_ntoa(addrClient.sin_addr);
//		sprintf(tempBuf, "%s said: %s\n", ipClient, recvBuf);
//		printf("%s", tempBuf);
//		gets(sendBuf);
//		//��������
//		sendto(svr, sendBuf, strlen(sendBuf) + 1, 0, (sockaddr*)&addrClient, len);
//	}
//	closesocket(svr);
//	WSACleanup();
//}

////TCP server
//
//#pragma comment(lib, "ws2_32.lib")
//#include <Winsock2.h>
//#include <stdio.h>
//void main()
//{
//	//�汾Э��
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//	wVersionRequested = MAKEWORD(1, 1); //0x0101
//	err = WSAStartup(wVersionRequested, &wsaData);
//	if (err != 0)
//	{
//		return;
//	}
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)  //wsaData.wVersion!=0x0101
//	{
//		WSACleanup();
//		return;
//	}
//	//����Socket
//	SOCKET sockSvr = socket(AF_INET, SOCK_STREAM, 0);
//	//����IP��ַ�Ͷ˿�
//	SOCKADDR_IN addrSvr;
//	addrSvr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	addrSvr.sin_family = AF_INET;
//	addrSvr.sin_port = htons(6000);
//	//�󶨶˿ڼ���
//	bind(sockSvr, (SOCKADDR*)&addrSvr, sizeof(SOCKADDR));
//	listen(sockSvr, 5);
//	sockaddr_in addrClient;
//	int len = sizeof(sockaddr);
//	while (true)
//	{
//		//�������������һ���ͻ�Socket����
//		SOCKET sockConn = accept(sockSvr, (sockaddr*)&addrClient, &len);
//		char sendbuffer[128];
//		sprintf(sendbuffer, "Welcom %s!", inet_ntoa(addrClient.sin_addr));
//		//��ͻ�Socket��������
//		send(sockConn, sendbuffer, strlen(sendbuffer) + 1, 0);
//		char recvbuffer[128];
//		//�ӿͻ�Soc��������
//		recv(sockConn, recvbuffer, 128, 0);
//		printf("%s\n", recvbuffer);
//		//�ر�Socket
//		closesocket(sockConn);
//	}
//	closesocket(sockSvr);
//	//�ͷ�Winsock��Դ
//	WSACleanup();
//}



//tcp server select
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "WS2_32")	

int main()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);

	USHORT nPort = 4567;	// �˷����������Ķ˿ں�

	// ���������׽���
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	// ���׽��ֵ����ػ���
	if (::bind(sListen, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf(" Failed bind() \n");
		return -1;
	}
	// �������ģʽ
	::listen(sListen, 5);

	// selectģ�ʹ������
	// 1����ʼ��һ���׽��ּ���fdSocket����Ӽ����׽��־�����������
	fd_set fdSocket;		// ���п����׽��ּ���
	FD_ZERO(&fdSocket);
	FD_SET(sListen, &fdSocket);
	while (TRUE)
	{
		// 2����fdSocket���ϵ�һ������fdRead���ݸ�select������
		// �����¼�����ʱ��select�����Ƴ�fdRead������û��δ��I/O�������׽��־����Ȼ�󷵻ء�
		fd_set fdRead = fdSocket;
		int nRet = ::select(0, &fdRead, NULL, NULL, NULL);
		if (nRet > 0)
		{
			// 3��ͨ����ԭ��fdSocket������select�������fdRead���ϱȽϣ�
			// ȷ��������Щ�׽�����δ��I/O������һ��������ЩI/O��
			for (int i = 0; i < (int)fdSocket.fd_count; i++)
			{
				if (FD_ISSET(fdSocket.fd_array[i], &fdRead))
				{
					if (fdSocket.fd_array[i] == sListen)		// ��1�������׽��ֽ��յ�������
					{
						if (fdSocket.fd_count < FD_SETSIZE)
						{
							sockaddr_in addrRemote;
							int nAddrLen = sizeof(addrRemote);
							SOCKET sNew = ::accept(sListen, (SOCKADDR*)&addrRemote, &nAddrLen);   //���ڽ��յ���������
							FD_SET(sNew, &fdSocket);
							printf("���յ����ӣ�%s��\n", ::inet_ntoa(addrRemote.sin_addr));
						}
						else
						{
							printf(" Too much connections! \n");
							continue;
						}
					}
					else
					{
						char szText[256];
						int nRecv = ::recv(fdSocket.fd_array[i], szText, strlen(szText), 0);
						if (nRecv > 0)						// ��2���ɶ�
						{
							szText[nRecv] = '\0';
							printf("���յ����ݣ�%s \n", szText);
						}
						else								// ��3�����ӹرա����������ж�
						{
							::closesocket(fdSocket.fd_array[i]);
							printf("���ӹر�,,,");
							FD_CLR(fdSocket.fd_array[i], &fdSocket);
						}
					}
				}
			}
		
		else
		{
			printf(" Failed select() \n");
			break;
		}
	}

	WSACleanup();
	return 0;
}