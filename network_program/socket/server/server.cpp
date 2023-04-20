#include "server.h"

Server::Server(unsigned short port)
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
    serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    // 创建socket
    sServer = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定socket
    int bindRet = bind(sServer, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));
    if (bindRet == SOCKET_ERROR) {
        std::cout << "bind error." << std::endl;
        WSACleanup();
    }
    else
        std::cout << "bind succeed." << std::endl;

    // 监听socket
    int listenRet = listen(sServer, SOMAXCONN);
    if (listenRet < 0) {
        std::cout << "listen error." << std::endl;
        WSACleanup();
    }
    else
        std::cout << "listen succeed." << std::endl;

    std::cout << "server listening..." << std::endl;

    // 阻塞等待 接受连接
    int len = sizeof(SOCKADDR);
    sAccept = accept(sServer, (SOCKADDR*)&acceptAddr, &len);
    if (sAccept == SOCKET_ERROR) {
        std::cout << "connect error." << std::endl;
        WSACleanup();
    }
    else {
        std::cout << "connect succeed." << std::endl;

        // 循环接收数据
        while (true)
        {
            // 接收消息
            recvLen = recv(sAccept, recvBuf, sizeof(recvBuf), 0);
            if (recvLen < 0) {
                std::cout << "receive error." << std::endl;
                break;
            }
            else
                std::cout << "client message: " << recvBuf << std::endl;
            
            // 发送消息
            std::cout << "send message: ";
            std::cin >> sendBuf;
            sendLen = send(sAccept, sendBuf, sizeof(sendBuf), 0);
            if (sendBuf < 0) {
                std::cout << "send error." << std::endl;
                break;
            }

            // 输入q结束
            if (strcmp(sendBuf, "q") == 0 || strcmp(recvBuf, "q") == 0) {
                std::cout << "enter \"q\", close..." << std::endl;
                break;
            } 
        }

        // 关闭socket
        closesocket(sServer);
        closesocket(sAccept);
        WSACleanup();
    }
}

Server::~Server()
{

}
                   
int main()      
{  
    Server s(8888);
    return 0;      
}  