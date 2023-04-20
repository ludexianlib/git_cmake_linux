#include <winsock.h>   
#include <stdio.h>     
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
    Client(unsigned short port);
    ~Client();
private:
    SOCKET sServer;
    SOCKADDR_IN serverAddr;
    int recvLen;
    int sendLen;
    char recvBuf[100];
    char sendBuf[100];
};