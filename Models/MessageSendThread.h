#pragma once

#include <QThread>
#include <QTcpSocket>
#include "Messages.h"

class MessageSendThread : public QThread
{
	Q_OBJECT
protected:
	Messages *sendMsg;
	QTcpSocket* socket;

public:
	bool isGoing;
	MessageSendThread(QTcpSocket* parent);
	MessageSendThread(const MessageSendThread& new_thread);
	void SetMessagesAndStart(Messages* msgs);
	~MessageSendThread();
	bool isBusing;
	MessageSendThread& operator=(const MessageSendThread& m);
protected:
	virtual void run() override;
	
};