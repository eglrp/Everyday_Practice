//#pragma comment (lib,"ws2_32.lib")
//#include <Winsock2.h>
//#include <stdio.h>
//
//// udp Client
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
//	//�����������׽���
//	SOCKET Svr = socket(AF_INET, SOCK_DGRAM, 0);
//	//������ַ
//	SOCKADDR_IN addrSvr;
//	addrSvr.sin_family = AF_INET;
//	addrSvr.sin_port = htons(6000);
//	addrSvr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	char recvBuf[128];
//	char sendBuf[128];
//	int len = sizeof(sockaddr);
//	while (true)
//	{
//		printf("client frist send message:\n");
//		gets(sendBuf);
//		//��������
//
//		sendto(Svr, sendBuf, strlen(sendBuf) + 1, 0, (sockaddr*)&addrSvr, len);   //sendBuf�������ڴ�����ʾ��ASCII�롣
//		//��������
//		recvfrom(Svr, recvBuf, 128, 0, (sockaddr*)&addrSvr, &len);
//		char* ipSvr = inet_ntoa(addrSvr.sin_addr);
//		printf("%s said: %s\n", ipSvr, recvBuf);
//	}
//	closesocket(Svr);
//	WSACleanup();
//}
//

//TCP client

//#pragma comment (lib,"ws2_32.lib")
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
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) 	//wsaData.wVersion!=0x0101
//	{
//		WSACleanup();
//		return;
//	}
//	//����������������׽���
//	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
//	//������ַ��Ϣ
//	SOCKADDR_IN hostAddr;
//	hostAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	hostAddr.sin_family = AF_INET;
//	hostAddr.sin_port = htons(6000);
////	while (1)
//	{
//		//���ӷ�����
//		connect(sock, (sockaddr*)&hostAddr, sizeof(sockaddr));
//		char revBuf[128];
//		//�ӷ������������
//		recv(sock, revBuf, 128, 0);
//		printf("%s\n", revBuf);
//		//���������������
//		send(sock, "Hello Host!", 12, 0);
//		closesocket(sock);
//	}
//	//closesocket(sock);
//	////�ͷ�Winsock��Դ
//	//WSACleanup();
//}


//tcp client select
#include <Winsock2.h>
#include <stdio.h>
#pragma comment (lib,"Ws2_32.lib")


int main(void)
{
	//�����׽���
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA lpWSAData;
	WSAStartup(wVersionRequested, &lpWSAData);

	//����socket
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(4567);

	//����
	if (connect(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("����ʧ��\n");
		return 0;
	}

	char Sendbuff[100] = { 0 };
	sprintf(Sendbuff, "this zhangsan");
	send(sockSrv, Sendbuff, strlen(Sendbuff + 1), 0);

	closesocket(sockSrv);
	WSACleanup();
	getchar();
	return 0;
}
