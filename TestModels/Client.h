#pragma once
#include "../Models/UserInfoProtocol.h"
//#include <QTcpSocket>
#include <QtNetwork\QTcpSocket>

#include "../Models/Message.h"
#include <QHostAddress>
#include <QDataStream>
#include "../Models/MessageSendThread.h"
#include "../Models/CommandBody.h"
#include "../Models/TextBody.h"
#include <QDebug>
#include "../Models/Messages.h"
#include "../Models/MessageCatch.h"
#include "../Models/MessageFactory.h"

class Client : public QTcpSocket,public UserInfoProtocol
{
	Q_OBJECT

public:
	Client(QObject *parent= nullptr);
	Client(qintptr socketDescriptor, QObject* parent = nullptr);
	~Client();

//clientinfo
public:
	//bool isEmpty;
	bool isLogin;
	QString password;
	QString ipAddress;
	int port;

public:
	virtual void setName(QString name) override;
	virtual void setNickName(QString nickName) override;
	void setPassword(QString password);

protected:

	virtual QJsonObject appendToSonsJson(QJsonObject* obj) override;
	virtual void appendToSonsValue(QJsonObject* obj) override;

signals:
	void signalClientInfoChanged();


	//QTcpSocket
private:
	MessageCatch *messageCatch;
	MessageSendThread *messageSendThread;
	//QThread catchThread;

public:
	Messages *messages;
	
	//MyClient(qintptr socketDescriptor, QObject* parent = nullptr);
	//MyClient(const MyClient& c);

	//~MyClient();
	void sendMessage(Message& msg);
	//MyClient& operator=(const MyClient&);

signals:
	//void signalReciveNewMessage(Message*);
	void signalClientHaveNewMessage(bool isSend,Message);
	//void signalCatchFinished();
private slots:

	//void temp();
	void  readMessage();

	//void startCatchMessage();
	void slotCatchRecivedMessage(Message msg);
	void slotConnected();
};
