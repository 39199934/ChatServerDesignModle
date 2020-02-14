#include "MessageSendThread.h"

MessageSendThread::MessageSendThread(QTcpSocket* parent)
	: QThread(parent),
	socket(parent),
	isBusing(false),
	sendMsg(nullptr),
	isGoing(true)
{
}

MessageSendThread::MessageSendThread(const MessageSendThread& new_thread):
	QThread(new_thread.parent()),
	sendMsg(new_thread.sendMsg),
	socket(new_thread.socket),
	isBusing(new_thread.isBusing)
{
}

void MessageSendThread::SetMessagesAndStart(Messages* msgs)
{
	this->sendMsg = msgs;
	this->start();
}

MessageSendThread::~MessageSendThread()
{
}

void MessageSendThread::run()
{
	while (isGoing)
	{
		qDebug() << "In Message send thread," << QThread::currentThread();
		auto count = sendMsg->getMessagesCount();
			for (int i = 0; i < count; i++) {
				auto sm = sendMsg->getMessageStruct(i);
				isBusing = true;
				if (sm.isSendType && (!sm.isSended)) {
					socket->write(sm.msg.head.toBytes());
					socket->waitForBytesWritten();
					msleep(100);
					socket->write(sm.msg.body->toBytes());
					socket->waitForBytesWritten();
					sendMsg->markedIsSended(i);
					msleep(300);
				}
			}
		isBusing = false;
		msleep(1000);
	}

}

MessageSendThread& MessageSendThread::operator=(const MessageSendThread& m) {
	QThread::QThread(m.parent());
	this->sendMsg = m.sendMsg;
	this->socket = m.socket;
	this->isBusing = m.isBusing;
	return *this;
}