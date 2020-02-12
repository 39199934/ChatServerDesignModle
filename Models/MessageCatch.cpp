#include "MessageCatch.h"

MessageCatch::MessageCatch(QTcpSocket* socket)
	: QThread(socket),
	socket(socket),
	isFinished(false)
{
}

MessageCatch::~MessageCatch()
{
}

void MessageCatch::run()
{
	qDebug() << "in message catch" << QThread::currentThread();
	QByteArray bytes;
	bytes = socket->readAll();
	Message* msg = nullptr;
	QJsonDocument doc = QJsonDocument::fromJson(bytes);
	if (doc.isEmpty()) {
		TextBody* text = new TextBody(QString::fromLocal8Bit(bytes),"noSender", "noReciver");
		msg = new Message(text, socket);
		
	}
	else {
		//qDebug() << doc;

		auto obj = doc.object();
		QStringList keys = { "size","version","uuid" };
		if (obj.contains("size")  && obj.contains("version") && obj.contains("uuid")) {
			auto head = new MessageHead();
			auto size = obj.value("size").toInt();
			head->fromBytes(bytes);
			int readedSize = 0;
			QByteArray bodyBytes;
			while (readedSize < size) {
				if (socket->isReadable()) {
					auto b = socket->readAll();
					readedSize += b.size();
					bodyBytes.append(b);
				}
				msleep(200);

			}
			BodyProtocol* bodyProtocol = nullptr;
			QJsonParseError error;
			auto doc = QJsonDocument::fromJson(bodyBytes, &error);
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
				}
				else if (type == "command") {
					bodyProtocol = new CommandBody();

				}
				else
				{

				}
				bodyProtocol->fromBytes(bodyBytes);
			}


			//return bodyProtocol;
			//auto body = MessageFactory::BodyFactory(bodyBytes);
			msg = new Message(head, bodyProtocol,parent());
			qDebug() << bodyProtocol->getBag();
		}

	}
	emit signalMessageIsReady(msg);
	isFinished = true;
}
