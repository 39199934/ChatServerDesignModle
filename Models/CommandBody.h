#pragma once
#include "BodyProtocol.h"
#include <QJsonArray>
#include "ClientInfo.h"

class CommandBody :
	public BodyProtocol
{
protected:

	virtual QJsonObject appendToSonsJson(QJsonObject* obj);
	virtual void appendToSonsValue(QJsonObject* obj);
public:
	QString commandType;
	QString commandName;
	QJsonArray commandDetail;
public:
	CommandBody();
	CommandBody(QString command_type,QString command_name,QJsonArray command_detail, QString sender = QString(), QString reciver = QString());
	virtual QString getDescription() override;
	virtual void run(ServerInfo* serverInfo, Clients* clients, ClientInfo* info) override;
};

