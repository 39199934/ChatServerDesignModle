#pragma once
#include "UserInfoProtocol.h"
#include "Message.h"
class ClientInfo :
	public UserInfoProtocol
{
private:
	QString password;
	QString ipAddress;
	int port;
public:
	ClientInfo();
	ClientInfo(QString name, QString nick_name,QString pass_word);

	void setClientInfo(QString name, QString nick_name, QString pass_word);

	
protected:
	
	virtual QJsonObject appendToSonsJson(QJsonObject* obj) override;
	virtual void appendToSonsValue(QJsonObject* obj) override;

public:
	void setIpAddress(QString addr);
	void setPort(int port);
	QString getIpAddress();
	int getPort();

	virtual QString getDescription() override;
	
};

