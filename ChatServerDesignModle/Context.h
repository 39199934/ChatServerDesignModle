#pragma once

#include <QObject>
#include "Clients.h"
#include "ServerSetting.h"
#include "QTextEdit"

class Context : public QObject
{
	Q_OBJECT

public:
	
	~Context();
	static Context* getContext(QObject* parent = nullptr);
	Clients* getClients();
	ServerSetting* getServerSetting();
	QTextEdit* messageViewer;
	void setMessageViewr(QTextEdit* viewer);
private:
	Context(QObject* parent);
	static Context* context;
	static Clients* clients;
	static ServerSetting* serverSetting;



};
