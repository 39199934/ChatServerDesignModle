#pragma once

#include <QTcpServer>
#include "ServerSetting.h"
#include "MyClient.h"
#include <QVector>
#include "Message.h"
#include "TextBody.h"
#include "Clients.h"
#include <QTextEdit>
#include "Context.h"

class MyServer : public QTcpServer
{
	Q_OBJECT

private:
	ServerSetting * setting;
	Clients* clients;
	QTextEdit* messageHistoryViewer;
	Context* context;
	
public:
	MyServer(Context* new_context,QObject *parent);
	~MyServer();	

	void start();
	void stop();

	int findClientInClients(MyClient* client);
	void sendMessageToAll(Message* msg);

	void setMessageHistoryViewer(QTextEdit* viewer);

	
public slots:

	void slotReciveMessage(Message* msg);
protected:
	virtual void incomingConnection(qintptr socketDescriptor) override;
};
