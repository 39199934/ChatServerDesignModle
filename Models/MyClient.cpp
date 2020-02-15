#include "MyClient.h"




using namespace std;
MyClient::MyClient(qintptr socketDescriptor, QObject* parent):
	QTcpSocket(parent),
	clientInfo(ClientInfo()),
	messages(Messages(this)),
	messageSendThread(MessageSendThread(this)),
	messageCatch(MessageCatch(this))
{
	//QTcpSocket::QTcpSocket(this);
	auto rt = setSocketDescriptor(socketDescriptor);

	connect(this, &MyClient::readyRead, this, &MyClient::readMessage);
	connect(&messageCatch, &MessageCatch::signalMessageIsReady, this, &MyClient::slotCatchRecivedMessage);

	//»º´æÏûÏ¢
	//connect(&catchThread, &QThread::started, this, &MyClient::startCatchMessage);
	//connect(this, &MyClient::signalClientHaveNewMessage, &catchThread, &QThread::quit);
	//this->setParent(nullptr);
	//this->moveToThread(&catchThread);

	
	BodyProtocol* text = new TextBody("this is a msg", "server", "client");
	qDebug() << "text *" << text;
	Message* msg =new  Message(text, this);
	qDebug() << "in Client construct Message" << msg << " thread:" << QThread::currentThread();
	//messages.append(msg);
	this->sendMessage(*msg);
	//msg->send(this);
	
	clientInfo.setIpAddress(this->peerAddress().toString());
	clientInfo.setPort(this->peerPort());
	//this->write("hello ,client");
	messageSendThread.SetMessagesAndStart(&messages);

	

}

MyClient::MyClient(const MyClient& c):
	QTcpSocket(c.parent()),
	clientInfo(c.clientInfo),
	messages(c.messages),
	messageSendThread(c.messageSendThread),
	messageCatch(c.messageCatch)
{
	connect(this, &MyClient::readyRead, this, &MyClient::readMessage);
	connect(&messageCatch, &MessageCatch::signalMessageIsReady, this, &MyClient::slotCatchRecivedMessage);

	
	

	clientInfo.setIpAddress(this->peerAddress().toString());
	clientInfo.setPort(this->peerPort());
	//this->write("hello ,client");
	messageSendThread.SetMessagesAndStart(&messages);
}



MyClient::~MyClient()
{
	messageSendThread.isGoing = false;
	messageSendThread.quit();
	for (int i = 0; i < messages.getMessagesCount(); i++) {
		auto sm = messages.getMessageStruct(i);
		if (sm.msg.body) {
			delete sm.msg.body;
			sm.msg.body = nullptr;
		}
		
	}
	this->close();
	
}

void MyClient::sendMessage(Message& msg)
{
	
	qDebug() << "in ~Message" << &msg << " thread:" << QThread::currentThread();
	//messageSendThread.SetMessagesAndStart(msg);
	
	messages.appendMessage(true,msg);
	emit signalClientHaveNewMessage(msg);
}
/*
void MyClient::appendMessage(Message msg)
{
	messages.push_back(&msg);
	//emit signalReciveNewMessage(msg);
	emit signalClientHaveNewMessage(msg);
}
*/
void MyClient::readMessage()
{
	qDebug() <<"in Myclient"<< QThread::currentThread();
	messageCatch.start();
	
}
/*
void MyClient::startCatchMessage()
{
	qDebug() << "in message catch" << QThread::currentThread();
	QByteArray bytes;
	bytes =readAll();
	Message msg;
	QJsonDocument doc = QJsonDocument::fromJson(bytes);
	if (doc.isEmpty()) {
		
		msg = Message(new TextBody(QString::fromLocal8Bit(bytes), "noSender", "noReciver"), nullptr);

	}
	else {
		//qDebug() << doc;

		auto obj = doc.object();
		QStringList keys = { "size","version","uuid" };
		if (obj.contains("size") && obj.contains("version") && obj.contains("uuid")) {
			auto head = MessageHead();
			auto size = obj.value("size").toInt();
			head.fromBytes(bytes);
			int readedSize = 0;
			QByteArray bodyBytes;
			qDebug() << "In Catch Thread:" << QThread::currentThread();
			while (readedSize < size) {
				if (isReadable()) {
					auto b = readAll();
					readedSize += b.size();
					bodyBytes.append(b);
				}
				QThread::msleep(200);

			}
			BodyProtocol* bodyProtocol ;
			QJsonParseError error;
			auto doc = QJsonDocument::fromJson(bodyBytes, &error);
			auto obj = doc.object();
			if ((error.error != QJsonParseError::NoError) || (doc.isEmpty()) || (!obj.contains("type"))) {

			}
			else {
				auto type = obj.value("type").toString();
				if (type == "text") {
					bodyProtocol =  new TextBody();
					//auto textBody = new TextBody();
					///textBody->fromBytes(body);
					//bodyProtocol = textBody;
				}
				else if (type == "command") {
					bodyProtocol = new CommandBody();

				}
				else
				{

				}
				bodyProtocol->fromBytes(bodyBytes);
			}


			//return bodyProtocol;
			//auto body = MessageFactory::BodyFactory(bodyBytes);
			msg =  Message(head, bodyProtocol,this);
			qDebug() << bodyProtocol->getBag()<<"   \r\nuser  is:";

		}

	}
	
	messages.appendMessage(false, msg);
	emit signalClientHaveNewMessage(msg);
	
	
}*/

void MyClient::slotCatchRecivedMessage(Message msg)
{
	messages.appendMessage(false, msg);
	emit signalClientHaveNewMessage(msg);
}


MyClient& MyClient::operator=(const MyClient& m)
{
	this->setParent(m.parent());
	this->clientInfo= (m.clientInfo);
	this->messages = (m.messages);
	this->messageSendThread = m.messageSendThread;
	return *this;
}