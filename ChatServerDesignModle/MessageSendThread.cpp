#include "MessageSendThread.h"

MessageSendThread::MessageSendThread(QTcpSocket* parent)
	: QThread(parent),
	socket(parent),
	isBusing(false),
	sendMsg(nullptr)
{
}



void MessageSendThread::sendMessage(Message* msg)
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
	socket->write(sendMsg->head->toBytes());
	socket->waitForBytesWritten();
	msleep(2000);
	socket->write(sendMsg->body->toBytes());
	socket->waitForBytesWritten();
	isBusing = false;

}