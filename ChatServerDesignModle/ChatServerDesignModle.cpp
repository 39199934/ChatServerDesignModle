#include "ChatServerDesignModle.h"

ChatServerDesignModle::ChatServerDesignModle(QWidget *parent)
	: QMainWindow(parent),
	server(new MyServer(this))
{
	ui.setupUi(this);
	server->listen(QHostAddress::Any, 5666);
	
	//connect()
	//ui.menuBar->menu
	connect(ui.cActionServerState, &QAction::triggered, this, &ChatServerDesignModle::onChangeedServerStat);
	server->start();
	ui.cActionServerState->setChecked(true);
	ui.cToolBarServerState->setCheckable(true);
}

ChatServerDesignModle::~ChatServerDesignModle()
{
	//serve
	
	delete server;
}

void ChatServerDesignModle::onChangeedServerStat()
{
	if (server->isListening()) {
		server->stop();
		ui.cActionServerState->setChecked(false);
		ui.cToolBarServerState->setCheckable(false);

	}
	else {
		server->start();
		ui.cActionServerState->setChecked(true);
		ui.cToolBarServerState->setCheckable(true);
	}
}
