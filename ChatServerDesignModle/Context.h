#pragma once

#include <QObject>
#include "Clients.h"
//#include "ServerInfo.h"
#include "ServerSetting.h"
class Context : public QObject
{
	Q_OBJECT

public:
	Context(QObject *parent);
	~Context();

	static Context* getConText(QObject * parent);

	Clients* getClients();
	ServerSetting* getServerSetting();
private:
	static Context* context;
	static Clients* clients;
	static ServerSetting* serverSetting;
};
