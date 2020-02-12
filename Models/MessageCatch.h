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
	void signalMessageIsReady(Message* msg);
private:
	QTcpSocket* socket;
public:
	bool isFinished;
	MessageCatch(QTcpSocket * socket);
	~MessageCatch();
protected:
	virtual void run() override;
};
