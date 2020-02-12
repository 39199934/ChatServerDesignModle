#pragma once

#include <QTcpServer>
#include "ServerInfo.h"
#include "MyClient.h"
#include <QVector>
#include "Message.h"
#include "TextBody.h"
#include <QTextEdit>
#include "Clients.h"


class MyServer : public QTcpServer
{
	Q_OBJECT

private:
	ServerInfo* info;
	//Clients* clients;
	QTextEdit* messageHistoryViewer;
	
	
public:
	MyServer(ServerInfo* info,QObject *parent);
	~MyServer();	

	void start();
	void stop();

	//int findClientInClients(MyClient* client);
	//void sendMessageToAll(Message* msg);

	//void setMessageHistoryViewer(QTextEdit* viewer);

	
public slots:

	void slotReciveMessage(Message* msg);

signals:
	void signalNewClientConnected(qintptr socketDescriptor);
protected:
	virtual void incomingConnection(qintptr socketDescriptor) override;
};
