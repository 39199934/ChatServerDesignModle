#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatClientDesignModle.h"
#include "../Models/Message.h"

class ChatClientDesignModle : public QMainWindow
{
	Q_OBJECT

public:
	ChatClientDesignModle(QWidget *parent = Q_NULLPTR);
	Message msg;

private:
	Ui::ChatClientDesignModleClass ui;
};
