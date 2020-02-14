#include "MyServer.h"

MyServer::MyServer(ServerInfo  info, QObject* parent)
	: QTcpServer(parent),
	info(info)
	/*,
	setting(new_context->getServerSetting()),
	clients(new_context->getClients()),
	messageHistoryViewer(new_context->messageViewer)*/
{
	//setting->loadSetting();

}

MyServer::MyServer(const MyServer& m):
	QTcpServer(m.parent()),
	info(m.info)
{
}

MyServer::~MyServer()
{

}

void MyServer::start()
{
	this->listen(QHostAddress::Any, info.serverPort);
}

void MyServer::stop()
{
	//TextBody text("server is closed", "server", "all");
	//Message *msg = new Message(&text, this);
	//sendMessageToAll(msg);
	//clients->disConnectToAll();
	
	this->close();
}

/*
void MyServer::sendMessageToAll(Message* msg)
{
	clients->sendMessageToAll(msg);
}

void MyServer::setMessageHistoryViewer(QTextEdit* viewer)
{
	this->messageHistoryViewer = viewer;
}
*/


void MyServer::incomingConnection(qintptr socketDescriptor)
{
	
	emit signalNewClientConnected(socketDescriptor);
	
}
