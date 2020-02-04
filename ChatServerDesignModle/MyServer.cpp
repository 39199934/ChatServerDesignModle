#include "MyServer.h"

MyServer::MyServer(QObject *parent)
	: QTcpServer(parent),
	setting(ServerSetting()),
	clients(new Clients())
{
	setting.loadSetting();

}

MyServer::~MyServer()
{

	if (clients) {
		delete clients;
	}
}

void MyServer::start()
{
	this->listen(QHostAddress::Any, setting.serverPort);
}

void MyServer::stop()
{
	TextBody text("server is closed", "server", "all");
	Message *msg = new Message(&text, this);
	sendMessageToAll(msg);
	clients->disConnectToAll();
	
	this->close();
}


void MyServer::sendMessageToAll(Message* msg)
{
	clients->sendMessageToAll(msg);
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
	auto client = clients->appendClient(socketDescriptor);
	client->write("hello client");
	
}
