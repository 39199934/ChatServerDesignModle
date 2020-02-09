#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatServerDesignModle.h"
#include "MyServer.h"
#include <QAbstractItemModel>
#include <QMessageBox>

class ChatServerDesignModle : public QMainWindow
{
	Q_OBJECT

public:
	ChatServerDesignModle(QWidget *parent = Q_NULLPTR);
	MyServer* server;
	~ChatServerDesignModle();
	
public slots:
	void onChangeedServerStat();
	void onClickedBtnSend();

private:
	Ui::ChatServerDesignModleClass ui;
	int getSelectedIndex();
};
