#include "MyServer.h"

MyServer::MyServer(QObject *parent)
	: QTcpServer(parent),
	setting(new ServerSetting()),
	clients(new Clients(parent)),
	messageHistoryViewer(nullptr)
{
	setting->loadSetting();

}

MyServer::~MyServer()
{

	if (clients) {
		delete clients;
	}
}

void MyServer::start()
{
	this->listen(QHostAddress::Any, setting->serverPort);
}

void MyServer::stop()
{
	TextBody text("server is closed", "server", "all");
	Message *msg = new Message(&text, this);
	sendMessageToAll(msg);
	clients->disConnectToAll();
	
	this->close();
}


MyClient* MyServer::findClientByIndex(int index)
{
	return clients->findClientByIndex(index);
}

void MyServer::sendMessageToAll(Message* msg)
{
	clients->sendMessageToAll(msg);
}

void MyServer::sendMessageToClient(int index, Message* msg)
{
	auto client = this->findClientByIndex(index);
	if (!client) {
		return;
	}
	client->sendMessage(msg);
}

void MyServer::setMessageHistoryViewer(QTextEdit* viewer)
{
	this->messageHistoryViewer = viewer;
}

void MyServer::slotReciveMessage(Message* msg)
{
	if (!messageHistoryViewer) {
		return;
	}
	messageHistoryViewer->append(msg->body->getDescription());
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
	auto client = clients->appendClient(socketDescriptor);
	client->write("hello client");
	connect(client, &MyClient::signalClientHaveNewMessage, this, &MyServer::slotReciveMessage);
	
}
