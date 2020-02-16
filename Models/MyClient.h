#pragma once

#include <QTcpSocket>
#include "UserInfoProtocol.h"
#include "ClientInfo.h"
#include "Message.h"
#include <QHostAddress>
#include <QDataStream>
#include "MessageSendThread.h"
#include "CommandBody.h"
#include "TextBody.h"
#include <QDebug>
#include "Messages.h"
#include "MessageCatch.h"
//class MessageCatch;
class MyClient : public QTcpSocket
{
	Q_OBJECT


protected:
	MessageCatch messageCatch;
	MessageSendThread messageSendThread;
	//QThread catchThread;
	QThread sendThread;
public:
	Messages messages;
	ClientInfo clientInfo;
	//MyClient(QObject *parent);
	MyClient(qintptr socketDescriptor, QObject* parent = nullptr);
	MyClient(const MyClient& c);

	~MyClient();
	void sendMessage(Message& msg);
	MyClient& operator=(const MyClient&);
	
signals:
	//void signalReciveNewMessage(Message*);
	void signalClientHaveNewMessage(Message);
	void signalCatchFinished();
public slots:
	
	void  readMessage();

	//void startCatchMessage();
	void slotCatchRecivedMessage(Message msg);

	

};
