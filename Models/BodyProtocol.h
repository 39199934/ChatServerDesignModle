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
	virtual void setValue();////��Ҫ�̳У����ڴ�doc��ת��Ϊ�����е�value���� �ڻ����е���
	virtual void setDocument();///��Ҫ�̳У����ڴ�value��ת��Ϊ�����е�doc����


	virtual QJsonObject appendToSonsJson(QJsonObject* obj) =0;
	virtual void appendToSonsValue(QJsonObject* obj)=0;

	

	
public:
	QString sender;
	QString reciver;
	QString type;
};

