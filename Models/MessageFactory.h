#pragma once
#include "Message.h"
#include "MessageHead.h"
#include "Bodys.h"

#include "ServerInfo.h"
#include "UserInfoProtocol.h"
#include "ClientInfo.h"
#include <QVector>
#include "MyClient.h"

class MessageFactory
{
public:
	enum CommandFactoryType {
		login,
		loginup,
		clients,
		serverInfo,
		updateServerInfo
	};
	//static Message fromBytes(QByteArray& head, QByteArray& body);
	static BodyProtocol* BodyFactory(QByteArray& body);
	static Message BuildTextMessage(QString text,ServerInfo serverInfo, ClientInfo clientInfo);
	static Message BuildCommandMessage(CommandFactoryType type, ServerInfo serverInfo, ClientInfo clientInfo,QVector<ClientInfo> clientInfos);
	static Message BuildCommandMessage(CommandFactoryType type, ServerInfo serverInfo, Clients* clients, MyClient* client);
};

