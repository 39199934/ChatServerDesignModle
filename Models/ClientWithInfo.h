#pragma once
#include <qvector.h>
#include "ClientInfo.h"
#include "MyClient.h"
#define ClientInfosFileName "clientInfos.dat"
class ClientWithInfo:public MyClient,public ClientInfo
{
public:
	/*struct ClientWithInfo {
		ClientInfo info;
		bool isLoginIn;
		int clientsIndex;
	};*/

	ClientWithInfo(qintptr socketDescriptor, QString name, QString nick_name, QString pass_word, QObject* parent = nullptr);
	~ClientWithInfo();
protected:
	//QVector<ClientWithInfo> infos;
	//bool saveInfos(QString fileName);
	//void loadInfos(QString fileName);


};

