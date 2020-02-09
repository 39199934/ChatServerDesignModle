#pragma once
#include "Message.h"
#include "MessageHead.h"
#include "Bodys.h"

#include "Context.h"
class Context;
class MessageFactory
{
public:
	enum CommandFactoryType {
		login,
		clients,
		serverInfo
	};
	static Message* fromBytes(QByteArray& head, QByteArray& body);
	static BodyProtocol* BodyFactory(QByteArray& body);
	static Message* BuildCommandMessage(CommandFactoryType type, Context* context);
	
};

