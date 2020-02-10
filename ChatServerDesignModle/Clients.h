//客户端集合类


#pragma once
#include <QVector>
#include "MyClient.h"
#include <QAbstractItemModel>
#include <QAbstractTableModel>


class Clients: public QAbstractTableModel
{

private:
	QVector<MyClient*> clients;
public:
	Clients(QObject * parent = nullptr);
	virtual ~Clients();


	int getCount();
	MyClient* appendClient(MyClient* client);
	MyClient* appendClient(qintptr socketDescriptor);
	bool removeClient(MyClient* client);
	bool replacClient(int index, MyClient* new_client);
	int  findClient(MyClient* client);//找到返回索引值 ，没找到返回-1
	MyClient* findClient(int index);

	void disConnectToAll();


	void sendMessageToAll(Message* msg);


public:
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

};

