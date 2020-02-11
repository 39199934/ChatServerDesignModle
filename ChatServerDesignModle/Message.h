#pragma once

#include <QObject>
#include "MessageHead.h"
#include "BodyProtocol.h"
#include <QTcpSocket>


class Message : public QObject
{
	Q_OBJECT

public:
	Message(QObject *parent= nullptr);
	Message(BodyProtocol* new_body, QObject* parent = nullptr);
	Message(MessageHead * new_head, BodyProtocol* new_body, QObject* parent = nullptr);
	
	Message(const Message&);

	~Message();
	MessageHead* head;
	BodyProtocol* body;

	void send(QTcpSocket* socket);

};
