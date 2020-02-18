#include "LoginData.h"

LoginData::LoginData(QObject *parent)
	: QObject(parent)
{
	load();
}

LoginData::~LoginData()
{
	save();
}

void LoginData::save()
{
	QFile fp(LoginDataFileName);
	QDataStream out(&fp);
	fp.open(QIODevice::WriteOnly);
	out<< this->clientCount << this->clients;
	fp.close();
}

void LoginData::load()
{
	QFile fp(LoginDataFileName);
	QDataStream in(&fp);
	fp.open(QIODevice::ReadOnly);
	in >> this->clientCount >> this->clients;
	fp.close();
}

LoginData* LoginData::loginData = nullptr;
