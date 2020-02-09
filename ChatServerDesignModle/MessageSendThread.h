#pragma once

#include <QThread>
#include <QTcpSocket>
#include "Message.h"

class MessageSendThread : public QThread
{
	Q_OBJECT
private:
	Message* sendMsg;
	QTcpSocket* socket;

public:
	MessageSendThread(QTcpSocket *parent);
	void sendMessage(Message* msg);
	~MessageSendThread();
	bool isBusing;
protected:
	virtual void run() override;
};
