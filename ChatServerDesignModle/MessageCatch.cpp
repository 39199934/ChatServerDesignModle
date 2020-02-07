#include "MessageCatch.h"

MessageCatch::MessageCatch(QTcpSocket* socket, QObject* parent )
	: QThread(parent),
	socket(socket),
	isFinished(false)
{
}

MessageCatch::~MessageCatch()
{
}

void MessageCatch::run()
{
	QByteArray bytes;
	bytes = socket->readAll();
	Message* msg = nullptr;
	QJsonDocument doc = QJsonDocument::fromJson(bytes);
	if (doc.isEmpty()) {
		TextBody* text = new TextBody(QString::fromLocal8Bit(bytes),"noSender", "noReciver");
		msg = new Message(text, this);
		
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
			auto body = MessageFactory::BodyFactory(bodyBytes);
			msg = new Message(head, body,parent());
			qDebug() << body->getBag();
		}

	}
	emit signalMessageIsReady(msg);
	isFinished = true;
}
