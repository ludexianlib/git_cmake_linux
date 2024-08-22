#pragma once
#include <QThread>
#include <QTcpSocket>

class SocketThread : public QThread
{
public:
    SocketThread(QObject* parent = nullptr);
    ~SocketThread();

protected:
    void run() override;

private:
    QTcpSocket* m_socket = nullptr;
};
