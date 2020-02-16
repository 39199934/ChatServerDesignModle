#include "MessageFactory.h"
/*
Message MessageFactory::fromBytes(QByteArray& h, QByteArray& b)
{
	BodyProtocol* body;
	auto bodyObj = QJsonDocument::fromJson(b).object();
	auto type = bodyObj.value("type").toString();
	//if (type = )
	return nullptr;
}
*/
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
Message MessageFactory::BuildTextMessage(QString text, ServerInfo serverInfo, ClientInfo clientInfo)
{
	
	QString reciver;
	if (clientInfo.isEmpty) {
		reciver = "all";
	}
	else
	{
		reciver = clientInfo.getUuid();
	}
	auto sender = serverInfo.getUuid();
	auto body = new TextBody(text, sender,reciver );
	qDebug() << "in factory,body address:" << body;
	auto msg =  Message(body);
	return msg;
}
Message MessageFactory::BuildCommandMessage(CommandFactoryType type, ServerInfo serverInfo, ClientInfo clientInfo, QVector<ClientInfo> clientInfos)
{
	//auto serverSetting = context->getServerSetting();// getServerSetting();
	//auto clients = context->getClients();
	return Message();
}

Message MessageFactory::BuildCommandMessage(CommandFactoryType type, ServerInfo serverInfo, Clients* clients,MyClient* client)
{
	Message msg;
	QJsonArray array;
	CommandBody* body;
	switch (type)
	{
	case MessageFactory::login:
		break;
	case MessageFactory::clients:
		break;
	case MessageFactory::serverInfo:
		break;
	case MessageFactory::updateServerInfo:
		
		array.insert(0, serverInfo.toObject());
		body = new CommandBody("answer", "updateServerInfo", array,serverInfo.getUuid(),client->clientInfo.getUuid());
		msg = Message(body, client);
		qDebug() << body->toObject();
		break;
	default:
		break;
	}
	return msg;
}
