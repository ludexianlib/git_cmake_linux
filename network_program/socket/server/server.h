#include <winsock.h>   
#include <stdio.h> 
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

class Server
{
public:
    Server(unsigned short port);
    ~Server();
private:
    SOCKET sServer;
    SOCKET sAccept;
    SOCKADDR_IN serverAddr;
    SOCKADDR_IN acceptAddr;
    int recvLen;
    int sendLen;
    char recvBuf[100];
    char sendBuf[100];
};