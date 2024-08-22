#include "SocketThread.h"

SocketThread::SocketThread(QObject* parent) : QThread(parent)
{
}

SocketThread::~SocketThread()
{
    // quit()
    // wait()
    // ��ʱexec()�˳��߳�
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
			// ��ǰ��������Ҫ��ѯ��1����û�н�������ٴβ�ѯ
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