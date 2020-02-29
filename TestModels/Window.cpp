#include "Window.h"
#include "../Models/MessageFactory.h"


Window::Window(QWidget *parent)
	: QWidget(parent),
	client(new Client(this))
{
	ui.setupUi(this);
	connect(client, &Client::connected, this, &Window::slotConnected);
	client->setName("ro");
	client->setNickName("lodestar");
	client->setPassword("801103");
	client->connectToHost("127.0.0.1", 5666);
	

}

Window::~Window()
{
	if (client) {
		delete client;
	}
}

void Window::viewMessage(QString str)
{
	//ui.textBro
	ui.textBrowser->append(str);
	ui.textBrowser->append("\n");
	
}

void Window::slotConnected()
{
	viewMessage("client did connect to host");
}
