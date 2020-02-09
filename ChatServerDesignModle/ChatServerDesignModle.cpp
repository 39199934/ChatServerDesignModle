#include "ChatServerDesignModle.h"

ChatServerDesignModle::ChatServerDesignModle(QWidget *parent)
	: QMainWindow(parent),
	context(Context::getContext(this))
{
	
	server = new MyServer(context, this);
	ui.setupUi(this);
	context->setMessageViewr(ui.cMessageHistory);
	server->listen(QHostAddress::Any, 5666);
	ui.cListView->setModel(context->getClients());
	ui.tableView->setModel(context->getClients());
	server->setMessageHistoryViewer(ui.cMessageHistory);
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
