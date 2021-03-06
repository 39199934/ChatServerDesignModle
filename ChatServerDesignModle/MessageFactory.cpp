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
Message* MessageFactory::BuildTextMessage(QString text,int clientIndex)
{
	auto context = Context::getContext();
	QString reciver;
	if (clientIndex < 0) {
		reciver = "all";
	}
	else
	{
		reciver = context->getClients()->findClient(clientIndex)->clientInfo->getUuid();
	}
	auto sender = context->getServerSetting()->serverInfo->getUuid();
	auto body = new TextBody(text, sender,reciver );
	auto msg = new Message(body);
	return msg;
}
Message* MessageFactory::BuildCommandMessage(CommandFactoryType type, Context* context)
{
	auto serverSetting = context->getServerSetting();// getServerSetting();
	auto clients = context->getClients();
	return nullptr;
}
