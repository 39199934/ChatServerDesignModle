#include "ClientWithInfo.h"



ClientWithInfo::ClientWithInfo(qintptr socketDescriptor, QString name, QString nick_name, QString pass_word, QObject* parent):
	MyClient(socketDescriptor,parent),
	ClientInfo(name,nick_name,pass_word)

{
}

ClientWithInfo::~ClientWithInfo()
{
	saveInfos(ClientInfosFileName);
}
