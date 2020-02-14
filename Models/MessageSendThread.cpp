#include "MessageSendThread.h"

MessageSendThread::MessageSendThread(QTcpSocket* parent)
	: QThread(parent),
	socket(parent),
	isBusing(false),
	sendMsg(Message())
{
}

MessageSendThread::MessageSendThread(const MessageSendThread& new_thread):
	QThread(new_thread.parent()),
	sendMsg(new_thread.sendMsg),
	socket(new_thread.socket),
	isBusing(new_thread.isBusing)
{
}

void MessageSendThread::sendMessage(Message& msg)
{
	this->sendMsg = msg;
	this->start();
}

MessageSendThread::~MessageSendThread()
{
}

void MessageSendThread::run()
{
	isBusing = true;
	socket->write(sendMsg.head.toBytes());
	socket->waitForBytesWritten();
	msleep(2000);
	socket->write(sendMsg.body->toBytes());
	socket->waitForBytesWritten();
	isBusing = false;

}

MessageSendThread& MessageSendThread::operator=(const MessageSendThread& m) {
	QThread::QThread(m.parent());
	this->sendMsg = m.sendMsg;
	this->socket = m.socket;
	this->isBusing = m.isBusing;
	return *this;
}