#include "MyServer.h"

MyServer::MyServer(QObject *parent)
	: QTcpServer(parent),
	setting(ServerSetting()),
	clients(QVector<MyClient *>())
{
	setting.loadSetting();

}

MyServer::~MyServer()
{
	for each( auto client in clients)
	{
		if (client) {
			client->write("bye");
		
			delete client;
		}
	}
}

void MyServer::start()
{
	this->listen(QHostAddress::Any, setting.serverPort);
}

void MyServer::stop()
{
	this->close();
}

int MyServer::findClientInClients(MyClient* client)
{
	int index = 0;
	for(int i=0 ;i<clients.count;i++)
	{
		auto c = clients.at(i);
		if (c == client) {
			return i;

		}
		else {
			index++;
		}
	}
	return -1;
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
	MyClient* client = new MyClient(socketDescriptor, this);
	client->write("hello client");
	clients.append(client);
}
