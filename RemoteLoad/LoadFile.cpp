#include<Windows.h>
#include<iostream>
#include <stdlib.h> 
#pragma comment(lib, "ws2_32.lib")

char* remoteLoad(const char* host, int port, const char* filename) {
	WSADATA data;
	LPSTR ipstr = (char*)host;
	int err = WSAStartup(MAKEWORD(2, 2), &data);

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = inet_addr(ipstr);
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sock, (SOCKADDR*)&si, sizeof(si));
	if (sock == -1 || sock == -2) {
		return 0;
	}

	char request[1024] = "GET /";
	strcat_s(request, filename);
	strcat_s(request, " HTTP/1.1\r\nHost:");
	strcat_s(request, host);
	strcat_s(request, "\r\nConnection:Close\r\n\r\n");
	int ret = send(sock, request, strlen(request), 0);
	const int bufsize = 4096;
	char* buf = (char*)calloc(bufsize, 1);
	ret = recv(sock, buf, bufsize - 1, 0);
	while (TRUE) {
		if (*buf == '\x0d' && *(buf + 1) == '\x0a' && *(buf + 2) == '\x0d' && *(buf + 3) == '\x0a')
			break;
		else
			buf++;
	}
	buf += 4;
	closesocket(sock);
	WSACleanup();
	return buf;
}