#pragma once

#include <QtWidgets\QWidget>
#include "ui_Window.h"
#include "Client.h"

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR);
	~Window();

private:
	Ui::Window ui;
	Client* client;
	void viewMessage(QString str);
public slots:

	void slotConnected();
};
