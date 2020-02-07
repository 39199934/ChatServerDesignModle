#pragma once

#include <QTcpSocket>
#include "UserInfoProtocol.h"
#include "ClientInfo.h"
#include "Message.h"
#include <QHostAddress>
#include <QDataStream>
#include "MessageCatch.h"

class MyClient : public QTcpSocket
{
	Q_OBJECT


private:
	MessageCatch* messageCatch;
public:
	QVector<Message*> messages;
	ClientInfo* clientInfo;
	//MyClient(QObject *parent);
	MyClient(qintptr socketDescriptor, QObject* parent = nullptr);
	~MyClient();
	void sendMessage(Message* msg);

	
signals:
	void signalReciveNewMessage(Message*);
public slots:
	void appendMessage(Message* msg);
	void  readMessage();

};
