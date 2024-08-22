#include "SocketThread.h"

SocketThread::SocketThread(QObject* parent) : QThread(parent)
{
}

SocketThread::~SocketThread()
{
    // quit()
    // wait()
    // 此时exec()退出线程
}

void SocketThread::run()
{
    m_socket = new QTcpSocket();
    connect(m_socket, &QTcpSocket::connected, this, &TCPProcessThread::onConnected, Qt::DirectConnection);
	connect(m_socket, &QTcpSocket::disconnected, this, &TCPProcessThread::onDisconnected, Qt::DirectConnection);
	connect(m_socket, &QTcpSocket::readyRead, this, &TCPProcessThread::onReadyRead, Qt::DirectConnection);

	// m_socket->connectHost();
	// m_overtime.start();

	QTimer timer;
	connect(&timer, &QTimer::timeout, [=]() {
		if (/* !socket connect */)
		{
			// m_socket->connectHost();
		}
		else
		{
			// 当前有数据需要查询，1秒内没有结果返回再次查询
			if (/* m_overtime.hasExpired(1000) */)
			{
				m_socket->write(/* data */);
				// m_overtime.restart();
			}
		}

	});

	timer.start(50);
	exec();
	delete m_tcpSocket;
}