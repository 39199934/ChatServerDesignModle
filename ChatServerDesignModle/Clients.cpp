#include "Clients.h"

Clients::~Clients()
{
	foreach(auto c, clients) {
		if (c) {
			delete c;
		}
	}
}

Clients::Clients(QObject* parent):
	QAbstractTableModel(parent),
	clients(QVector<MyClient *>())
{
}

int Clients::getCount()
{
	return clients.count();
}

MyClient* Clients::appendClient(MyClient* client)
{
	if (findClient(client) != -1) {
		return nullptr;
	}
	if (!client) {
		return nullptr;
	}

	beginInsertRows(QModelIndex(), 0, clients.count());
	clients.append(client);
	endInsertRows();
	
	return client;
}

MyClient* Clients::appendClient(qintptr socketDescriptor)
{
	
	MyClient* client = new MyClient(socketDescriptor, nullptr);
	
	return appendClient(client);
	
}

bool Clients::removeClient(MyClient* client)
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

bool Clients::replacClient(int index, MyClient* new_client)
{
	if (index < getCount()) {
		beginInsertColumns(QModelIndex(), 0, clients.count());
		clients.replace(index, new_client);
		endInsertRows();
		return true;
	}
	return false;
}

int Clients::findClient(MyClient* client)
{
	for (int index = 0 ; index < clients.count(); index++) {
		if (clients.at(index) == client) {
			return index;
		}
	}
	return -1;
}

void Clients::disConnectToAll()
{
	for (int index = 0; index < clients.count(); index++) {
		clients.at(index)->close();
	}
}

void Clients::sendMessageToAll(Message* msg)
{
	for (int index= 0; index < clients.count(); index++) {
		clients.at(index)->sendMessage(msg);
	}
}

QVariant Clients::data(const QModelIndex& index, int role) const
{
	if (Qt::DisplayRole == role) {
		auto info = clients[index.row()]->clientInfo;
		if (index.column() == 0) {
			return info->getDescription();
		}
		if (index.column() == 1) {
			return info->name;
		}
		if (index.column() == 2) {
			return info->getUuid();
		}
		
	}
	return QVariant();
}

int Clients::columnCount(const QModelIndex& parent) const
{
	return 3;
}

Qt::ItemFlags Clients::flags(const QModelIndex& index) const
{
	if(index.column() !=2)

		return index.flags() || Qt::ItemFlag::ItemIsEditable;
	else {
		return index.flags();
	}
	//return Qt::ItemFlags();
}

QVariant Clients::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (section == 0 && orientation == Qt::Horizontal) {
		return "昵称";
	}
	if (section == 1 && orientation == Qt::Horizontal) {
		return "登陆名";
	}
	if (section == 0 && orientation == Qt::Horizontal) {
		return "客户端识别号";
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
			this->clients[index.row()]->clientInfo->nickName = value.toString();
			return true;
		}
		if (index.column() == 1)
		{
			this->clients[index.row()]->clientInfo->name = value.toString();
			return true;
		}
		
	}
	return false;
}
