#include "ChatServerDesignModle.h"

ChatServerDesignModle::ChatServerDesignModle(QWidget *parent)
	: QMainWindow(parent),
	server(new MyServer(this))
{
	ui.setupUi(this);
	server->listen(QHostAddress::Any, 5666);
}

ChatServerDesignModle::~ChatServerDesignModle()
{
	server->close();
	delete server;
}
