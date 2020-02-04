#pragma once

#include <QTcpSocket>
#include "UserInfoProtocol.h"
#include "ClientInfo.h"
#include "Message.h"

class MyClient : public QTcpSocket
{
	Q_OBJECT


public:
	QVector<Message*> messages;
	UserInfoProtocol* clientInfo;
	//MyClient(QObject *parent);
	MyClient(qintptr socketDescriptor, QObject* parent = nullptr);
	~MyClient();
};
