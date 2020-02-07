#pragma once

#include <QThread>
#include <QTcpSocket>
#include "Message.h"
#include "Bodys.h"

class MessageCatch : public QThread
{
	Q_OBJECT

signals:
	void signalMessageIsReady(Message* msg);
private:
	QTcpSocket* socket;
public:
	bool isFinished;
	MessageCatch(QTcpSocket * socket,QObject *parent = nullptr);
	~MessageCatch();
protected:
	virtual void run() override;
};
