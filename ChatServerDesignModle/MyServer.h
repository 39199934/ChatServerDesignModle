#pragma once

#include <QTcpServer>
#include "ServerSetting.h"
#include "MyClient.h"
#include <QVector>

class MyServer : public QTcpServer
{
	Q_OBJECT

private:
	ServerSetting setting;

	QVector<MyClient*> clients;
public:
	MyServer(QObject *parent);
	~MyServer();

	void start();
	void stop();

	int findClientInClients(MyClient* client);
protected:
	virtual void incomingConnection(qintptr socketDescriptor) override;
};
