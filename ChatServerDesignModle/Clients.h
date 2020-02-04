//�ͻ��˼�����


#pragma once
#include <QVector>
#include "MyClient.h"
class Clients
{

private:
	QVector<MyClient*> clients;
public:
	Clients();
	virtual ~Clients();


	int getCound();
	MyClient* appendClient(MyClient* client);
	MyClient* appendClient(qintptr socketDescriptor);
	bool removeClient(MyClient* client);
	bool replacClient(int index, MyClient* new_client);
	int  findClient(MyClient* client);//�ҵ���������ֵ ��û�ҵ�����-1


	void disConnectToAll();


	void sendMessageToAll(Message* msg);
};

