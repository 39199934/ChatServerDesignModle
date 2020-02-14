#include "Messages.h"

Messages::Messages(QObject *parent)
	: QObject(parent),
	messages(QVector<MsgStruct>())
{
}

Messages::Messages(const Messages& m):
	QObject(m.parent()),
	messages(m.messages)
{
}
/*
Messages::Messages(const Messages& m):
	QObject(m.parent()),
	messages(m.messages)
{
}*/

Messages::~Messages()
{
}

Messages::MsgStruct Messages::getMessageStruct(int index)
{
	if (index >= 0 && index < messages.count()) {
		return messages[index];
	}
	return MsgStruct();
}

void Messages::appendMessage(bool is_send_type, Message msg)
{
	MsgStruct m;
	m.isSendType = is_send_type;
	m.isSended = false;
	m.msg = msg;
	messages.append(m);
}

int Messages::getMessagesCount()
{
	return messages.count();
}

Messages Messages::operator=(const Messages& msg)
{
	this->setParent(msg.parent());
	this->messages = msg.messages;
	return *this;
	}

void Messages::markedIsSended(int index)
{
	if (index < 0 && index >= messages.count()) {
		return;
	}
	messages[index].isSended = true;
}
