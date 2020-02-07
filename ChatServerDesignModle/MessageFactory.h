#pragma once
#include "Message.h"
#include "MessageHead.h"
#include "Bodys.h"

class MessageFactory
{
public:
	static Message* fromBytes(QByteArray& head, QByteArray& body);
	static BodyProtocol* BodyFactory(QByteArray& body);
};

