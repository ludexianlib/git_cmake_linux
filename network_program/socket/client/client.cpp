#include "client.h"     

Client::Client(unsigned short port)
{
    // 初始化socket
    WORD sVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    int error = WSAStartup(sVersion, &wsaData);
    if (error != 0)
        std::cout << "create error." << std::endl;
    else
        std::cout << "create succeed." << std::endl;
    
    // 检测版本
    if (LOBYTE(wsaData.wVersion) != 2 || 
        HIBYTE(wsaData.wHighVersion) != 2) {
            std::cout << "version error." << std::endl;
        }
    else
        std::cout << "version correct." << std::endl;

    // 填充信息
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(port);

    // 创建socket
    sServer = socket(AF_INET, SOCK_STREAM, 0);

    // 连接socket
    int connectRet = connect(sServer, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));
    if (connectRet == SOCKET_ERROR) {
        std::cout << "connect error." << std::endl;
        WSACleanup();
    }
    else
        std::cout << "connect succeed." << std::endl;

    while (true)
    {
        // 发送信息
        std::cout << "send message: ";
        std::cin >> sendBuf;
        sendLen = send(sServer, sendBuf, sizeof(sendBuf), 0);
        if (sendLen < 0) {
            std::cout << "send error." << std::endl;
            break;
        }

        // 接收信息
        recvLen = recv(sServer, recvBuf, sizeof(recvBuf), 0);
        if (sendLen < 0) {
            std::cout << "receive error." << std::endl;
            break;
        }
        else
            std::cout << "receive message: " << recvBuf << std::endl;

        // 输入q结束
        if (strcmp(sendBuf, "q") == 0 || strcmp(recvBuf, "q") == 0) {
            std::cout << "enter \"q\", close..." << std::endl;
            break;
        } 
    }
    
    // 关闭socket
    closesocket(sServer);
    WSACleanup();    
}   

Client::~Client()
{

}

int main()      
{      
    Client c(8888);
    return 0;
}  