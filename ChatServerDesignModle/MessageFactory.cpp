#include "MessageFactory.h"

Message* MessageFactory::fromBytes(QByteArray& h, QByteArray& b)
{
	BodyProtocol* body;
	auto bodyObj = QJsonDocument::fromJson(b).object();
	auto type = bodyObj.value("type").toString();
	//if (type = )
	return nullptr;
}

BodyProtocol* MessageFactory::BodyFactory(QByteArray& body)
{
	BodyProtocol* bodyProtocol = nullptr;
	QJsonParseError error;
	auto doc = QJsonDocument::fromJson(body, &error);
	auto obj = doc.object();
	if ((error.error != QJsonParseError::NoError) || (doc.isEmpty()) || (!obj.contains("type"))) {

	}
	else {
		auto type = obj.value("type").toString();
		if (type == "text") {
			bodyProtocol = new TextBody();
			//auto textBody = new TextBody();
			///textBody->fromBytes(body);
			//bodyProtocol = textBody;
		}else if(type == "command") {
			bodyProtocol = new CommandBody();
			
		}
		else
		{

		}
		bodyProtocol->fromBytes(body);
	}
	
	
	return bodyProtocol;
}

Message* MessageFactory::BuildTextMessage(QString textMessage, QString sender, QString reciver, QObject* parent)
{
	auto bodyText = new TextBody(textMessage, sender, reciver);
	auto message = new Message(bodyText, parent);
	return message;
}

Message* MessageFactory::BuildCommandMessage(QString command_type, QString command_name, QJsonArray command_detail, QString sender, QString reciver, QObject* parent)
{
	auto bodyCommand = new CommandBody(command_type, command_name, command_detail, sender, reciver);
	auto message = new Message(bodyCommand, parent);
	return message;
}

/*
Message* MessageFactory::BuildCommandMessage(CommandBody::CommandEnumType type, MyServer* server)
{
	auto clients = server->clients;
	auto client = clients->findClientByIndex(0);
	return nullptr;
}

Message* MessageFactory::BuildCommandMessage(CommandBody::CommandEnumType type, Context* context)
{
	context->serverInfo;
	return nullptr;
}
*/