#include "Clients.h"

Clients::~Clients()
{
	foreach(auto c, clients) {
		if (c) {
			delete c;
		}
	}
}

Clients::Clients():
	clients(QVector<MyClient *>())
{
}

int Clients::getCound()
{
	return clients.count();
}

MyClient* Clients::appendClient(MyClient* client)
{
	if (findClient(client) != -1) {
		return nullptr;
	}
	if (!client) {
		return nullptr;
	}
	clients.append(client);
	return client;
}

MyClient* Clients::appendClient(qintptr socketDescriptor)
{
	MyClient* client = new MyClient(socketDescriptor, nullptr);
	return appendClient(client);
	
}

bool Clients::removeClient(MyClient* client)
{
	auto index = findClient(client);
	if (index == -1) {
		return false;
	}
	clients.remove(index);
	return true;
}

bool Clients::replacClient(int index, MyClient* new_client)
{
	if (index < getCound()) {
		clients.replace(index, new_client);
		return true;
	}
	return false;
}

int Clients::findClient(MyClient* client)
{
	for (int index = 0 ; index < clients.count(); index++) {
		if (clients.at(index) == client) {
			return index;
		}
	}
	return -1;
}

void Clients::disConnectToAll()
{
	for (int index = 0; index < clients.count(); index++) {
		clients.at(index)->close();
	}
}

void Clients::sendMessageToAll(Message* msg)
{
	for (int index= 0; index < clients.count(); index++) {
		clients.at(index)->sendMessage(msg);
	}
}
