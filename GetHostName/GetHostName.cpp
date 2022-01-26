#include<winsock.h>
#pragma comment(lib, "WS2_32.lib")

char* getHostName() {
    WSADATA WSAData;
    char buf[256]="10.10.10.10";
    char hostName[256];
    if (!WSAStartup(MAKEWORD(2, 0), &WSAData))
    {
        if (!gethostname(hostName, sizeof(hostName)))
        {
            hostent* host = gethostbyname(hostName);
            if (host != NULL)
            {
                return inet_ntoa(*(struct in_addr*)*host->h_addr_list);
            }
        }
    }
    return buf;
}