#pragma once
//#include "Message.h"
//#include "MessageHead.h"
//#include "Bodys.h"
#include "MyServer.h"
//#include "Context.h"


//extern class Context;
class MessageFactory
{
public:
	static Message* fromBytes(QByteArray& head, QByteArray& body);
	static BodyProtocol* BodyFactory(QByteArray& body);
	static Message* BuildTextMessage(QString textMessage, QString sender = QString(), QString reciver = QString(), QObject* parent = nullptr);
	static Message* BuildCommandMessage(QString command_type, QString command_name, QJsonArray command_detail, QString sender = QString(), QString reciver = QString(), QObject* parent = nullptr);
	//static Message* BuildCommandMessage(CommandBody::CommandEnumType type, MyServer* server);
};

