#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatServerDesignModle.h"
#include "Context.h"
#include <QMessageBox>

//class MessageFactory;
class ChatServerDesignModle : public QMainWindow
{
	Q_OBJECT

public:
	ChatServerDesignModle(QWidget *parent = Q_NULLPTR);
	//MyServer* server;
	Context* context;
	
	~ChatServerDesignModle();
	int getCurrentSelectedIndex();
	
public slots:
	void onChangeedServerStat();
	void onClickedSendMessage();
	void onClickedAddMore();
	void slotNeedRefreshMessageViewer(MyClient&, Message);
	void slotListViewClicked(const QModelIndex& index);

private:
	Ui::ChatServerDesignModleClass ui;
};
