#include "MyClient.h"
#include "Message.h"
#include "TextBody.h"




MyClient::MyClient(qintptr socketDescriptor, QObject* parent):
	QTcpSocket(parent),
	clientInfo(new ClientInfo()),
	messages(QVector<Message *>()),
	messageCatch(new MessageCatch(this,this))
{
	setSocketDescriptor(socketDescriptor);
	TextBody text("this is a msg", "server", "client");
	Message *msg = new Message(&text, this);
	msg->send(this);
	messages.append(msg);
	clientInfo->setIpAddress(this->peerAddress().toString());
	clientInfo->setPort(this->peerPort());
	//this->write("hello ,client");

	connect(this, &MyClient::readyRead, this, &MyClient::readMessage);
	connect(messageCatch, &MessageCatch::signalMessageIsReady, this, &MyClient::appendMessage);
}

MyClient::~MyClient()
{
	if (clientInfo) {
		delete clientInfo;
	}
	for each (auto msg in messages)
	{
		if (msg) {
			delete msg;
		}

	}
}

void MyClient::sendMessage(Message* msg)
{
	messages.append(msg);
	msg->body->setReciver( clientInfo->getUuid());
	
	this->write(msg->head->toBytes());
	waitForBytesWritten();
	this->write(msg->body->toBytes());
	waitForBytesWritten();
}

void MyClient::appendMessage(Message* msg)
{
	messages.push_back(msg);
	emit signalReciveNewMessage(msg);
}

void MyClient::readMessage()
{
	messageCatch->start();
	
}


