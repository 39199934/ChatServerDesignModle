#pragma once

#include <QTcpServer>
#include "ServerSetting.h"
#include "MyClient.h"
#include <QVector>
#include "Message.h"
#include "TextBody.h"
#include "Clients.h"
#include <QTextEdit>

class MyServer : public QTcpServer
{
	Q_OBJECT

private:
	ServerSetting setting;
	QTextEdit* messageHistoryViewer;
	
public:
	MyServer(QObject *parent);
	~MyServer();

	void start();
	void stop();

	int findClientInClients(MyClient* client);
	void sendMessageToAll(Message* msg);

	void setMessageHistoryViewer(QTextEdit* viewer);

	Clients* clients;
public slots:

	void slotReciveMessage(Message* msg);
protected:
	virtual void incomingConnection(qintptr socketDescriptor) override;
};
