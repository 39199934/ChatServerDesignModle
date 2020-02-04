#pragma once

#include <QTcpServer>
#include "ServerSetting.h"
#include "MyClient.h"
#include <QVector>
#include "Message.h"
#include "TextBody.h"
#include "Clients.h"

class MyServer : public QTcpServer
{
	Q_OBJECT

private:
	ServerSetting setting;

	Clients* clients;
public:
	MyServer(QObject *parent);
	~MyServer();

	void start();
	void stop();

	int findClientInClients(MyClient* client);
	void sendMessageToAll(Message* msg);
protected:
	virtual void incomingConnection(qintptr socketDescriptor) override;
};
