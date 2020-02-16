#include "Clients.h"

Clients::~Clients()
{
	
}

Clients::Clients(QObject* parent):
	QAbstractTableModel(parent),
	clients(QVector<MyClient* >())
{
}

Clients::Clients(const Clients& c):
	QAbstractTableModel(c.parent()),
	clients(c.clients)
{
}





int Clients::getCount()
{
	return clients.count();
}
/*
MyClient* Clients::appendClient(MyClient* client)
{
	if (findClient(client) != -1) {
		return nullptr;
	}
	

	beginInsertRows(QModelIndex(), 0, clients.count());
	clients.append(client);
	
	endInsertRows();
	connect(&client, &MyClient::signalClientHaveNewMessage, this, &Clients::slotClientHasNewMessage);
	return &client;
}
*/

//添加新客户端
MyClient* Clients::appendClient(qintptr socketDescriptor)
{
	
	MyClient *client = new MyClient(socketDescriptor, this);
	if (findClient(client) != -1) {
		return nullptr;
	}


	beginInsertRows(QModelIndex(), 0, clients.count());
	clients.append(client);

	endInsertRows();
	connect(client, &MyClient::signalClientHaveNewMessage, this, &Clients::slotClientHasNewMessage);
	return client;
	
}
/*
bool Clients::removeClient(MyClient client)
{
	auto index = findClient(client);
	if (index == -1) {
		return false;
	}
	beginRemoveRows(QModelIndex(), 0, clients.count());
	clients.remove(index);
	endRemoveRows();
	
	return true;
}

*/
/*
bool Clients::replacClient(int index, MyClient new_client)
{
	if (index < getCount()) {
		beginInsertColumns(QModelIndex(), 0, clients.count());
		clients.replace(index, new_client);
		endInsertRows();
		return true;
	}
	return false;
}
*/
int Clients::findClient(MyClient* client)
{
	for (int index = 0 ; index < clients.count(); index++) {
		
		
		if (clients.at(index) == client) {
			return index;
		}
	}
	return -1;
}

MyClient* Clients::getClient(int index)
{
	if (index >= 0 && index < clients.count()) {
		return clients[index];
	}
	else
	{
		return nullptr;
	}
}

QVector<ClientInfo> Clients::getClientsInfo()
{
	QVector<ClientInfo> clientInfos = QVector<ClientInfo>();
	for each(auto client in clients) {
		clientInfos.push_back(client->clientInfo);
	}
	return clientInfos;
}

MyClient* Clients::findClient(int index)
{
	if (index >= clients.count() || index < 0) {
		return nullptr;
	}
	return clients[index];
	//return nullptr;
}

ClientInfo Clients::getClientInfo(int index)
{
	auto client = findClient(index);
	if (!client) {
		return ClientInfo("no find Info","not find Info","not find info");
	}
	else {
		return client->clientInfo;
	}
}

void Clients::disConnectToAll()
{
	for (int index = 0; index < clients.count(); index++) {
		findClient(index)->close();
	}
}

void Clients::sendMessageToAll(Message msg)
{
	for (int index= 0; index < clients.count(); index++) {
		findClient(index)->sendMessage(msg);
	}
}

bool Clients::sendMessage(int index, Message msg)
{
	auto client = findClient(index);
	if (client) {
		client->sendMessage(msg);
		return true;
	}
	return false;

}

QVariant Clients::data(const QModelIndex& index, int role) const
{
	if (Qt::DisplayRole == role) {
		auto info = clients[index.row()]->clientInfo;
		if (index.column() == 0) {
			return info.getDescription();
		}
		if (index.column() == 1) {
			return info.getName();
		}
		if (index.column() == 2) {
			return info.getUuid();
		}
		if (index.column() == 3) {
			return info.getIpAddress();
		}
		if (index.column() == 4) {
			return QString::number(info.getPort());
		}
		
	}
	return QVariant();
}

int Clients::columnCount(const QModelIndex& parent) const
{
	return 5;
}

Qt::ItemFlags Clients::flags(const QModelIndex& index) const
{
	
	auto column = index.column();
	if (column < 2) {
		auto oldFlag = QAbstractTableModel::flags(index);
		auto newFlag = oldFlag | Qt::ItemIsEditable;
		return newFlag;
	}
	else {
		return QAbstractTableModel::flags(index);
	}
	//return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
	//return Qt::ItemFlags();
}

QVariant Clients::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (Qt::DisplayRole == role)
	{
		if (section == 0 && orientation == Qt::Horizontal) {
			return QString::fromLocal8Bit("昵称");
		}
		if (section == 1 && orientation == Qt::Horizontal) {
			return QString::fromLocal8Bit("登陆名");
		}
		if (section == 2 && orientation == Qt::Horizontal) {
			return QString::fromLocal8Bit("客户端识别号");
		}
		if (section == 3 && orientation == Qt::Horizontal) {
			return QString::fromLocal8Bit("客户端地址");
		}
		if (section == 4 && orientation == Qt::Horizontal) {
			return QString::fromLocal8Bit("客户端端口号");
		}
	}
	return QVariant();
}

int Clients::rowCount(const QModelIndex& parent) const
{
	return clients.count();
}

bool Clients::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (Qt::EditRole == role) {
		if (index.column() == 0)
		{
			this->clients[index.row()]->clientInfo.setNickName( value.toString());
			return true;
		}
		if (index.column() == 1)
		{
			this->clients[index.row()]->clientInfo.setName( value.toString());
			return true;
		}
		
	}
	return false;
}

void Clients::slotClientHasNewMessage(Message msg)
{
	auto client = static_cast<MyClient*>(sender());
	emit signalClientHasNewMessage(client, msg);
	//emit ssss();
}
