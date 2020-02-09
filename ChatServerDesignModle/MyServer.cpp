#include "MyServer.h"

MyServer::MyServer(Context* new_context, QObject* parent)
	: QTcpServer(parent),
	setting(new_context->getServerSetting()),
	clients(new_context->getClients()),
	messageHistoryViewer(new_context->messageViewer)
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


void MyServer::sendMessageToAll(Message* msg)
{
	clients->sendMessageToAll(msg);
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
	connect(client, &MyClient::signalReciveNewMessage, this, &MyServer::slotReciveMessage);
	
}
