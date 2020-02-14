#pragma once

#include <QThread>
#include <QTcpSocket>
#include "Message.h"

class MessageSendThread : public QThread
{
	Q_OBJECT
protected:
	Message sendMsg;
	QTcpSocket* socket;

public:
	MessageSendThread(QTcpSocket* parent);
	MessageSendThread(const MessageSendThread& new_thread);
	void sendMessage(Message& msg);
	~MessageSendThread();
	bool isBusing;
	MessageSendThread& operator=(const MessageSendThread& m);
protected:
	virtual void run() override;
	
};