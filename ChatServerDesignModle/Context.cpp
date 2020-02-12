#include "Context.h"

Context::Context(QObject *parent)
	:QObject(parent),
	clients(new Clients(this)),
	serverInfo(new ServerInfo()),
	server(nullptr)
{
	server = new MyServer(serverInfo, this);
	connect(server, &MyServer::signalNewClientConnected, this, &Context::slotHasNewClientConnected);
	connect(clients, &Clients::signalClientHasNewMessage, this, &Context::slotHasNewMessage);
	server->start();
}

Context::~Context()
{
	
	if (serverInfo) {
		delete serverInfo;
	}
	if (clients) {
		delete clients; 
	}
	/*if (context) {
		delete context;
		//context = nullptr;
	}*/
}

Context* Context::getContext(QObject* parent)
{
	if (context == nullptr) {
		context = new Context(parent);
	}
	return context;
}
ServerInfo* Context::getServerInfo()
{
	return serverInfo;
}
Clients* Context::getClients()
{
	/*if (clients == nullptr) {
		clients = new Clients()
	}*/
	return clients;
}

MyClient* Context::getClient(int index)
{
	if (index >= 0 && index < clients->getCount()) {
		return clients->getClient(index);
	}
	return nullptr;
}

QVector<ClientInfo*> Context::getClientsInfo()
{
	return clients->getClientsInfo();
}

bool Context::sendTextMessage(int selectedRow, QString text)
{


	if (clients->getCount() <= 0) {
		emit signalHasError("对不起，没有客户端");
		return false;
	}
	if (selectedRow < -1 && selectedRow >= clients->getCount()) {
		emit signalHasError("对不起，客户端编号超出范围");
		return false;
	}

	auto msg = MessageFactory::BuildTextMessage(text, serverInfo, clients->getClientInfo(selectedRow));
	if (selectedRow == -1) {
		auto rt = QMessageBox::warning(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("对不起，你没有选择发送给谁，消息是否发送给所有客户端？"), QMessageBox::StandardButton::Cancel, QMessageBox::StandardButton::Apply);
		if (rt == QMessageBox::StandardButton::Apply) {
			clients->sendMessageToAll(msg);
			return true;
		}
		else {
			return false;
			
		}
		
	}
	else {

		clients->sendMessage(selectedRow, msg);
		return true;
	}

	return false;
}

void Context::refreshMessages(QTextEdit* viewer, int selectedRow)
{
	if (selectedRow == -1) {
		return;
	}
	auto client = clients->findClient(selectedRow);
	if (client) {
		refreshMessages(viewer, client);
	}
}

void Context::refreshMessages(QTextEdit* viewer, MyClient* client)
{
	auto messages = client->messages;
	auto uuid = client->clientInfo->getUuid();
	
	for each (auto msg in messages)
	{
		auto type = msg->body->type;
		if (uuid == msg->body->sender) {
			viewer->alignment();
			viewer->setAlignment(Qt::AlignmentFlag::AlignRight);
			viewer->append(QString::fromLocal8Bit("客户端说\r\n"));
			viewer->append(msg->body->getDescription());
		}else{
		//if (uuid == msg->body->reciver) {
			viewer->alignment();
			viewer->setAlignment(Qt::AlignmentFlag::AlignLeft);
			viewer->append(QString::fromLocal8Bit("服务器或其他客户端说\r\n"));
			auto des = msg->body->getDescription();
			viewer->append(msg->body->getDescription());
		}
	}
}




void Context::slotHasNewMessage(MyClient* client, Message* msg)
{
	emit signalNeedRefreshMessageViewer(client, msg);
}

void Context::slotHasNewClientConnected(qintptr socketDescriptor)
{
	auto client = clients->appendClient(socketDescriptor);
	client->write("hello client");
	//connect(client, &MyClient::signalClientHaveNewMessage, this, &MyServer::slotReciveMessage);
}

bool Context::serverIsListening()
{
	return server->isListening();
}
void Context::startServer()
{
	server->start();
}
void Context::closeServer()
{
	server->stop();
}
Context* Context::context = nullptr;
