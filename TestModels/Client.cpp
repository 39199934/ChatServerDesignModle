#include "Client.h"

Client::Client(QObject* parent)
	: QTcpSocket(parent),
	UserInfoProtocol("no name", "no nick name", BagProtocol::createUuid()),
	messageSendThread(new MessageSendThread(this)),
	messageCatch(new MessageCatch(this)),
	messages(new Messages(this)),
	isLogin(false)
{
	this->setDocument();
	messageSendThread->SetMessagesAndStart(messages);
	connect(this, &Client::readyRead, this, &Client::readMessage);
	connect(messageCatch, &MessageCatch::signalMessageIsReady, this, &Client::slotCatchRecivedMessage);
	connect(this, &QTcpSocket::connected, this, &Client::slotConnected);

}

Client::Client(qintptr socketDescriptor, QObject* parent):
	Client(parent)
{
	this->setSocketDescriptor(socketDescriptor);
}

Client::~Client()
{
	if (messageSendThread) {
		messageSendThread->isGoing = false;
		messageSendThread->quit();
		messageSendThread->wait();
		messageSendThread->deleteLater();
		//delete messageSendThread;
	}
	if (messageCatch) {
		messageCatch->quit();
		delete messageCatch;
	}
	qDebug() << this->state();
	if (this->state() == QAbstractSocket::SocketState::ConnectedState) {
		this->disconnectFromHost();
		this->waitForDisconnected();
	}
	if (messages) {
		delete messages;
	}
}

void Client::setName(QString name)
{
	UserInfoProtocol::setName(name);
	emit signalClientInfoChanged();
}

void Client::setNickName(QString nickName)
{
	UserInfoProtocol::setNickName(nickName);
	emit signalClientInfoChanged();
}

void Client::setPassword(QString password)
{
	this->password = password;
	this->setDocument();
	emit signalClientInfoChanged();
}

QJsonObject Client::appendToSonsJson(QJsonObject* obj)
{
	obj->insert("password", this->password);
	obj->insert("ipAddress", this->ipAddress);
	obj->insert("port", this->port);
	return *obj;
	
}

void Client::appendToSonsValue(QJsonObject* obj)
{
	this->password = obj->value("password").toString();
	this->ipAddress = obj->value("ipAddress").toString();
	this->port = obj->value("port").toInt();
}

void Client::sendMessage(Message& msg)
{
	qDebug() << "in ~Message" << &msg << " thread:" << QThread::currentThread();
	//messageSendThread.SetMessagesAndStart(msg);

	messages->appendMessage(true, msg);
	emit signalClientHaveNewMessage(true,msg);
}

void Client::readMessage()
{
	messageCatch->start();
}

void Client::slotCatchRecivedMessage(Message msg)
{
	messages->appendMessage(false, msg);
	emit signalClientHaveNewMessage(false,msg);
}

void Client::slotConnected()
{
	QJsonArray arra;
	arra.insert(0, this->toObject());
	auto body =new CommandBody("request", "updateClientInfo", arra,this->getUuid(),"server");
	auto msg = Message(body, this);
	sendMessage(msg);
}
