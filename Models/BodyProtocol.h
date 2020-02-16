#pragma once
#include "BagProtocol.h"
//#include "ServerInfo.h"
//#include "MyClient.h"
//#include "../Models/Clients.h"
//#include "UserInfoProtocol.h"
class ServerInfo;
class ClientInfo;
class Clients;
class BodyProtocol :
	public BagProtocol
{

public:
	BodyProtocol();
	BodyProtocol(QString type);
	BodyProtocol(QString type, QString sender, QString reciver);
	virtual ~BodyProtocol();
	//int getSize();
	
	//QString uuid;


	void setReciver(QString new_reciver);
	virtual QString getDescription() = 0;
	virtual void run(ServerInfo* serverInfo, Clients* clients,ClientInfo* info) = 0;
protected:
	virtual void setValue();////需要继承，用于从doc中转换为本类中的value数据 在基类中调用
	virtual void setDocument();///需要继承，用于从value中转换为本类中的doc数据


	virtual QJsonObject appendToSonsJson(QJsonObject* obj) =0;
	virtual void appendToSonsValue(QJsonObject* obj)=0;

	

	
public:
	QString sender;
	QString reciver;
	QString type;
};

