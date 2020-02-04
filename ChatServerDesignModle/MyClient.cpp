#include "MyClient.h"
#include "Message.h"
#include "TextBody.h"




MyClient::MyClient(qintptr socketDescriptor, QObject* parent):
	QTcpSocket(parent),
	clientInfo(new ClientInfo()),
	messages(QVector<Message *>())
{
	setSocketDescriptor(socketDescriptor);
	TextBody text("this is a msg", "server", "client");
	Message *msg = new Message(&text, this);
	msg->send(this);
	messages.append(msg);
	//this->write("hello ,client");
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
