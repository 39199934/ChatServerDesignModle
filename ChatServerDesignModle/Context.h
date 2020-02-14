#pragma once

#include <QObject>
#include "../Models/Clients.h"
#include "../Models/ServerInfo.h"
#include <QTextEdit>
#include "../Models/MyServer.h"
#include "../Models/MessageCatch.h"
#include "../Models/MessageFactory.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QColor>
#include <QRgb>

class Context : public QObject
{
	Q_OBJECT

public:
	
	~Context();
	static Context* getContext(QObject* parent = nullptr);
	
	ServerInfo getServerInfo();

	
	//QTextEdit* messageViewer;
	//void setMessageViewr(QTextEdit* viewer);

signals:
	void signalHasError(QString errorDescription);
	void signalNeedRefreshMessageViewer(MyClient& client, Message msg);

	
	

public slots:
	//void slotNeedRefreshMessageViewer(MyClient* client, Message* msg);
	void slotHasNewMessage(MyClient& client, Message msg);


	//服务器所来消息处理槽
	void slotHasNewClientConnected(qintptr socketDescriptor);

public://涉及server 的外部接口
	bool serverIsListening();
	void startServer();
	void stopServer();
	//MyServer* getServer();
	
public://涉及Clients接口
	Clients* getClients();
	//MyClient* getClient(int index);
	//QVector<ClientInfo*> getClientsInfo();

	//ClientInfo* getClientInfo(int index);

public://涉及消息类的接口
	bool sendTextMessage(int selectedRow, QString text);
	void refreshMessages(QTextEdit* viewer,int selectedRow = -1);
	void refreshMessages(QTextEdit* viewer, MyClient& client);

private:
	class CGarbo //它的唯一工作就是在析构函数中删除CSingleton的实例
	{
	public:
		~CGarbo()

		{

			if (Context::context)

				delete Context::context;
			if (Context::server) {
				delete Context::server;
			}
			if (Context::clients) {
				delete Context::clients;
			}
			if (Context::serverInfo) {
				delete Context::serverInfo;
			}

		}

	};
	static CGarbo Garbo;
private:
	Context(QObject* parent);
	static Context* context;
	static Clients* clients;
	static ServerInfo* serverInfo;
	static MyServer* server;

	

	



};
