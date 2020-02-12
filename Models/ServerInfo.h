#pragma once
#include "BagProtocol.h"
#include "UserInfoProtocol.h"
#include <QSettings>
class ServerInfo :
	public UserInfoProtocol
{
private:

	QString iniFileName;

public:
	QString serverAddress;
	int serverPort;
public:
	ServerInfo();
	ServerInfo(QString name, QString nick_name);
	~ServerInfo();
	void setServerInfo(QString name, QString nick_name);

	void loadSetting();
	void saveSetting();
	
protected:
	virtual QJsonObject appendToSonsJson(QJsonObject * obj) override;
	virtual void appendToSonsValue(QJsonObject* obj) override;

	

};

