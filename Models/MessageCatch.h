#pragma once

#include <QThread>
#include <QTcpSocket>
#include "Message.h"
#include "Bodys.h"
//#include "MessageFactory.h"

class MessageCatch : public QThread
{
	Q_OBJECT

signals:
	void signalMessageIsReady(Message msg);
protected:
	QTcpSocket* socket;
public:
	bool isFinished;
	MessageCatch(QTcpSocket * socket);
	MessageCatch(const MessageCatch & m);
	~MessageCatch();
protected:
	virtual void run() override;
};
