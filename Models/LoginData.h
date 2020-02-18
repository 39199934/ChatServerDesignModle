#pragma once

#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QIODevice>
#define LoginDataFileName "loginData.dat"

class LoginData : public QObject
{
	Q_OBJECT

public:
	LoginData* getLoginData(QObject* parent = nullptr);
	struct LoginStruct {
		QString name;
		QString password;
	};

	void append(QString name, QString passoword);
	bool login(QString name, QString password);

private:
	LoginData(QObject *parent = nullptr);
	~LoginData();
	static LoginData* loginData;
	int clientCount;
	QVector<LoginStruct> clients;

	void save();
	void load();
};
