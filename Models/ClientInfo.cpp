#include "ClientInfo.h"

ClientInfo::ClientInfo() :
	UserInfoProtocol(),
	password(QString()),
	ipAddress("0.0.0.0"),
	port(0),
	isEmpty(true)
{
	//this->password = QString();
	this->setDocument();
}

ClientInfo::ClientInfo(QString name, QString nick_name, QString pass_word):
	UserInfoProtocol(name,nick_name),
	password(pass_word),
	ipAddress("0.0.0.0"),
	port(0),
	isEmpty(false)
{
	
	//setUserInfoProtocol(name, nick_name, pass_word);
	this->setDocument();
	createUuid();
}

QJsonObject ClientInfo::appendToSonsJson(QJsonObject* obj)
{
	obj->insert("password", this->password);
	obj->insert("ipAddress", this->ipAddress);
	obj->insert("port", this->port);
	return *obj;
}

void ClientInfo::appendToSonsValue(QJsonObject* obj)
{
	this->password = obj->value("password").toString();
	this->ipAddress = obj->value("ipAddress").toString();
	this->port = obj->value("port").toInt();
}

void ClientInfo::setIpAddress(QString addr)
{
	this->ipAddress = addr;
	this->setDocument();
}

void ClientInfo::setPort(int port)
{
	this->port = port;
	this->setDocument();
}

QString ClientInfo::getIpAddress()
{
	return this->ipAddress;
}

int ClientInfo::getPort()
{
	return this->port;
}

QString ClientInfo::getDescription()
{
	return this->getNickName() + " -- " + this->getIpAddress();
}

void ClientInfo::setClientInfo(QString name, QString nick_name, QString pass_word)
{
	UserInfoProtocol::setUserInfoProtocol(name, nick_name);
	this->password = pass_word;
	this->setDocument();
}

