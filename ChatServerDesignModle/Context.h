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

public://�漰server ���ⲿ�ӿ�
	bool serverIsListening();
	void startServer();
	void closeServer();
	
public://�漰Clients�ӿ�
	Clients* getClients();

private:
	class CGarbo //����Ψһ��������������������ɾ��CSingleton��ʵ��
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
