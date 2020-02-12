#include "ServerInfo.h"
#include <iostream>
using namespace std;

ServerInfo::ServerInfo() :
	UserInfoProtocol(),
	serverAddress("127.0.0.1"),
	serverPort(5666),
	iniFileName("ChatServer.ini")
{
	this->setDocument();
}

ServerInfo::ServerInfo(QString name, QString nick_name):
	UserInfoProtocol(name,nick_name),
	serverAddress("127.0.0.1"),
	serverPort(5666),
	iniFileName("ChatServer.ini")
{
	this->setDocument();
	createUuid();
	//setUserInfoProtocol(name, nick_name);
	this->setDocument();

}

ServerInfo::~ServerInfo()
{
	cout << "in ~ServerInfo" << endl;
}

QJsonObject ServerInfo::appendToSonsJson(QJsonObject* obj)
{
	obj->insert("serverAddress", this->serverAddress);
	obj->insert("serverPort", this->serverPort);
	obj->insert("iniFileName", this->iniFileName);
	
	return *obj;
}

void ServerInfo::appendToSonsValue(QJsonObject* obj)
{
	this->serverAddress = obj->value("serverAddress").toString();
	this->serverPort = obj->value("serverPort").toInt();
	this->iniFileName = obj->value("iniFileName").toString();
	return;
}

void ServerInfo::setServerInfo(QString name, QString nick_name)
{
	UserInfoProtocol::setUserInfoProtocol(name, nick_name);
	this->setDocument();
}


void ServerInfo::loadSetting()
{
	QSettings set(iniFileName, QSettings::IniFormat);
	this->serverAddress = set.value("serverAddress", serverAddress).toString();
	this->serverPort = set.value("serverPort", serverPort).toInt();
	auto bytes = set.value("info", QByteArray()).toByteArray();
	this->fromBytes(bytes);


	return;
}

void ServerInfo::saveSetting()
{
	QSettings set(iniFileName, QSettings::IniFormat);
	set.setValue("serverAddress", serverAddress);
	set.setValue("serverPort", serverPort);
	set.setValue("name", this->getName());
	set.setValue("nickName", this->getNickName());


}