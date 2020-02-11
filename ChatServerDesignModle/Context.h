#pragma once

#include <QObject>
#include "Clients.h"
#include "ServerSetting.h"
#include "QTextEdit"
#include "MyServer.h"
#include "MessageCatch.h"
#include "MessageFactory.h"


class Context : public QObject
{
	Q_OBJECT

public:
	
	~Context();
	static Context* getContext(QObject* parent = nullptr);
	
	ServerSetting* getServerSetting();
	
	QTextEdit* messageViewer;
	void setMessageViewr(QTextEdit* viewer);

public://涉及server 的外部接口
	bool serverIsListening();
	void startServer();
	void closeServer();
	
public://涉及Clients接口
	Clients* getClients();

private:
	class CGarbo //它的唯一工作就是在析构函数中删除CSingleton的实例
	{
	public:
		~CGarbo()

		{

			if (Context::context)

				delete Context::context;

		}

	};
	static CGarbo Garbo;
private:
	Context(QObject* parent);
	static Context* context;
	Clients* clients;
	ServerSetting* serverSetting;
	MyServer* server;

	

	



};
