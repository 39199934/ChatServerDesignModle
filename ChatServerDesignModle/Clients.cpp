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

MyClient* Clients::findClient(int index)
{
	if (index >= clients.count() || index < 0) {
		return nullptr;
	}
	return clients[index];
	//return nullptr;
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
			return info->getName();
		}
		if (index.column() == 2) {
			return info->getUuid();
		}
		if (index.column() == 3) {
			return info->getIpAddress();
		}
		if (index.column() == 4) {
			return QString::number(info->getPort());
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
			this->clients[index.row()]->clientInfo->setNickName( value.toString());
			return true;
		}
		if (index.column() == 1)
		{
			this->clients[index.row()]->clientInfo->setName( value.toString());
			return true;
		}
		
	}
	return false;
}
