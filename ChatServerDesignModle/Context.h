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
	class CGarbo //����Ψһ��������������������ɾ��CSingleton��ʵ��
	{
	public:
		~CGarbo()

		{

			if (Context::context)

				delete Context::context;

		}

	};
private:
	Context(QObject* parent);
	static Context* context;
	Clients* clients;
	ServerSetting* serverSetting;
	

	static CGarbo Garbo;



};
