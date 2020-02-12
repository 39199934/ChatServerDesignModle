#include "UserInfoProtocol.h"

UserInfoProtocol::UserInfoProtocol():
	BagProtocol()
{
	/*this->name = QString();
	this->nickName = QString();
	this->uuid = QString();*/
	setUserInfoProtocol(QString(), QString());
	
}

UserInfoProtocol::UserInfoProtocol(QString name, QString nick_name, QString user_uuid) :
	BagProtocol()
{
	setUserInfoProtocol(name, nick_name, user_uuid);

}

UserInfoProtocol::~UserInfoProtocol()
{
}

void UserInfoProtocol::setUserInfoProtocol(QString name, QString nick_name, QString user_uuid)
{
	if (!user_uuid.isEmpty()) {
		this->uuid = user_uuid;
	}

	
	this->name = name;
	this->nickName = nick_name;
	
	//setDocument();
	
}

QString UserInfoProtocol::getDescription()
{
	return this->nickName + "(" + this->name + ")";
}

void UserInfoProtocol::setValue()
{
	auto obj = getBag().object();
	this->name = obj.value("name").toString();
	this->nickName = obj.value("nickName").toString();
	this->uuid = obj.value("uuid").toString();
	this->appendToSonsValue(&obj);

}

void UserInfoProtocol::setDocument()
{
	QJsonObject obj;
	obj.insert("name", name);
	obj.insert("nickName", nickName);
	obj.insert("uuid", uuid);
	this->appendToSonsJson(&obj);
	fromJson(obj);

}
/*
void UserInfoProtocol::fromBytes(QByteArray bytes)
{
	BagProtocol::fromBytes(bytes);
	this->setValue();
}*/

void UserInfoProtocol::createUuid()
{
	this->uuid = BagProtocol::createUuid();
	auto obj = getBag().object();
	qDebug() << this->bag.toJson();
	obj["uuid"] = this->uuid;
	qDebug() << QJsonDocument(obj).toJson();

	fromJson(obj);

}

QString UserInfoProtocol::getName()
{
	this->setValue();
	return this->name;
}

QString UserInfoProtocol::getNickName()
{
	this->setValue();
	return this->nickName;
}

QString UserInfoProtocol::getUuid()
{
	this->setValue();
	return this->uuid;
}

void UserInfoProtocol::setName(QString name)
{
	this->name = name;
	this->setDocument();
}

void UserInfoProtocol::setNickName(QString nickName)
{
	this->nickName = nickName;
	this->setDocument();
}
