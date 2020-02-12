#pragma once

#include <QObject>
#include "../Models/Clients.h"
#include "../Models/ServerInfo.h"
#include <QTextEdit>
#include "../Models/MyServer.h"
#include "../Models/MessageCatch.h"
#include "../Models/MessageFactory.h"
#include <QMessageBox>



class Context : public QObject
{
	Q_OBJECT

public:
	
	~Context();
	static Context* getContext(QObject* parent = nullptr);
	
	ServerInfo* getServerInfo();

	
	//QTextEdit* messageViewer;
	//void setMessageViewr(QTextEdit* viewer);

signals:
	void signalHasError(QString errorDescription);
	void signalNeedRefreshMessageViewer(MyClient* client, Message* msg);

	
	

public slots:
	//void slotNeedRefreshMessageViewer(MyClient* client, Message* msg);
	void slotHasNewMessage(MyClient* client, Message* msg);


	//������������Ϣ�����
	void slotHasNewClientConnected(qintptr socketDescriptor);

public://�漰server ���ⲿ�ӿ�
	bool serverIsListening();
	void startServer();
	void closeServer();
	//MyServer* getServer();
	
public://�漰Clients�ӿ�
	Clients* getClients();
	MyClient* getClient(int index);
	QVector<ClientInfo*> getClientsInfo();

	ClientInfo* getClientInfo(int index);

public://�漰��Ϣ��Ľӿ�
	bool sendTextMessage(int selectedRow, QString text);
	void refreshMessages(QTextEdit* viewer,int selectedRow = -1);
	void refreshMessages(QTextEdit* viewer, MyClient* client);

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
	ServerInfo* serverInfo;
	MyServer* server;

	

	



};
