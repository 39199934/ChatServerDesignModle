#include "Context.h"

Context::Context(QObject *parent)
	:QObject(parent)
{
	;
	connect(server, &MyServer::signalNewClientConnected, this, &Context::slotHasNewClientConnected);
	connect(clients, &Clients::signalClientHasNewMessage, this, &Context::slotHasNewMessage);
	server->start();
}

Context::~Context()
{
	
	
	/*if (context) {
		delete context;
		//context = nullptr;
	}*/
}

Context* Context::getContext(QObject* parent)
{
	if (context == nullptr) {
		clients = new Clients(parent);
		serverInfo = new ServerInfo();
		server = new MyServer(*serverInfo, parent);
		context = new Context(parent);
	}
	return context;
}
/*
ServerInfo* Context::getServerInfo()
{
	return serverInfo;
}*/
Clients* Context::getClients()
{
	/*if (clients == nullptr) {
		clients = new Clients()
	}*/
	return clients;
}
/*
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
*/
bool Context::sendTextMessage(int selectedRow, QString text)
{


	if (clients->getCount() <= 0) {
		emit signalHasError("�Բ���û�пͻ���");
		return false;
	}
	if (selectedRow < -1 && selectedRow >= clients->getCount()) {
		emit signalHasError("�Բ��𣬿ͻ��˱�ų�����Χ");
		return false;
	}

	auto msg = MessageFactory::BuildTextMessage(text, *serverInfo, clients->getClientInfo(selectedRow));
	if (selectedRow == -1) {
		auto rt = QMessageBox::warning(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�Բ�����û��ѡ���͸�˭����Ϣ�Ƿ��͸����пͻ��ˣ�"), QMessageBox::StandardButton::Cancel, QMessageBox::StandardButton::Apply);
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
		refreshMessages(viewer, *client);
	}
}

void Context::refreshMessages(QTextEdit* viewer, MyClient& client)
{
	auto messages = client.messages;
	auto uuid = client.clientInfo.getUuid();
	
	for (int i = 0; i < messages.getMessagesCount(); i++) {
		auto msgStr = messages.getMessageStruct(i);
		auto msg = msgStr.msg;
		
		if (msgStr.isSendType) {
			viewer->setTextColor(Qt::GlobalColor::red);
			viewer->alignment();
			viewer->setAlignment(Qt::AlignmentFlag::AlignRight);
			viewer->append(QString::fromLocal8Bit("�ͻ���˵:"));
			viewer->append(msg.body->getDescription());
			
		}else{

			viewer->setTextColor(Qt::GlobalColor::blue);
		//if (uuid == msg->body->reciver) {
			viewer->alignment();
			viewer->setAlignment(Qt::AlignmentFlag::AlignLeft);
			viewer->append(QString::fromLocal8Bit("�������������ͻ���˵:"));
			auto des = msg.body->getDescription();
			viewer->append(msg.body->getDescription());
			
		}
		viewer->append("\n\n");
		QScrollBar* scrollbar = viewer->verticalScrollBar();
		if (scrollbar)
		{
			scrollbar->setSliderPosition(scrollbar->maximum());
		}
	}
}




void Context::slotHasNewMessage(MyClient& client, Message msg)
{
	emit signalNeedRefreshMessageViewer(client, msg);
}

void Context::slotHasNewClientConnected(qintptr socketDescriptor)
{
	auto client = clients->appendClient(socketDescriptor);
	auto msg = MessageFactory::BuildTextMessage("hello client", *serverInfo, client->clientInfo);
	qDebug() << "in Context,body address:" << msg.body;
	client->sendMessage(msg);
	
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
void Context::stopServer()
{
	server->stop();
}
Context* Context::context = nullptr;
Clients* Context::clients = nullptr;
ServerInfo* Context::serverInfo= nullptr;
MyServer* Context::server= nullptr;