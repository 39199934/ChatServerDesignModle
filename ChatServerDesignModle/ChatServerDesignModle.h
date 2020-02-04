#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatServerDesignModle.h"
#include "MyServer.h"

class ChatServerDesignModle : public QMainWindow
{
	Q_OBJECT

public:
	ChatServerDesignModle(QWidget *parent = Q_NULLPTR);
	QTcpServer* server;
	~ChatServerDesignModle();

private:
	Ui::ChatServerDesignModleClass ui;
};
