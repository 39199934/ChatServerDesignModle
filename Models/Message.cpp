#include "Message.h"
#include <QDebug>
#include <QThread>
using namespace std;

Message::Message(QObject *parent)
	: QObject(parent),
	body(nullptr)
{
	//cout << "hello" << endl;
	head = MessageHead();
}
Message::Message(const Message& newM):
	QObject(newM.parent()),
	body(newM.body)
{
	head = newM.head;
}

Message::Message(BodyProtocol* new_body, QObject* parent):
	QObject(parent),
	body(new_body)
{
	qDebug() << body;
	qDebug() << "origin *" << new_body;
	head = MessageHead();
	head.setHeadSize(body->getSize());
	//head = &h;
}

Message::Message(MessageHead new_head, BodyProtocol* new_body, QObject* parent):
	head(new_head),
	QObject(parent),
	body(new_body)
{
}

Message::~Message()
{
	qDebug() << "in ~Message" << this << " thread:" << QThread::currentThread();
	cout << "del message" << endl;
	if (body) {
		//delete body;
	}
}

Message Message::operator=(const Message& msg)
{
	this->setParent( msg.parent());
	this->head = msg.head;
	this->body = msg.body;
	return *this;
}

