#include "ChatServerDesignModle.h"

ChatServerDesignModle::ChatServerDesignModle(QWidget *parent)
	: QMainWindow(parent),
	context(Context::getContext(this))
{
	
	//server = new MyServer(context, this);
	ui.setupUi(this);
	//context->setMessageViewr(ui.cMessageHistory);
	//server->listen(QHostAddress::Any, 5666);
	ui.cListView->setModel(context->getClients());
	ui.tableView->setModel(context->getClients());
	//server->setMessageHistoryViewer(ui.cMessageHistory);
	//connect()
	//ui.menuBar->menu
	connect(ui.cActionServerState, &QAction::triggered, this, &ChatServerDesignModle::onChangeedServerStat);
	connect(ui.cBtnSend, &QPushButton::clicked, this, &ChatServerDesignModle::onClickedSendMessage);
	connect(ui.cBtnAddMore, &QPushButton::clicked, this, &ChatServerDesignModle::onClickedAddMore);


	connect(context, &Context::signalNeedRefreshMessageViewer, this, &ChatServerDesignModle::slotNeedRefreshMessageViewer);//  ChatServerDesignModle:slotNeedRefreshMessageViewer);
	//server->start();
	ui.cActionServerState->setChecked(true);
	ui.cToolBarServerState->setCheckable(true);
	
}

ChatServerDesignModle::~ChatServerDesignModle()
{
	//serve
	if (context) {
		delete context;
	}
	
}

int ChatServerDesignModle::getCurrentSelectedIndex()
{
	qDebug() << QThread::currentThread();
	auto sel = ui.cListView->selectionModel();
	if (!sel->hasSelection()) {
		return -1;
	}
	auto indexs = sel->selectedIndexes();
	auto row = indexs.at(0).row();
	//auto row = sel->selectedIndexes()[0].row();
	
	return row;
}

void ChatServerDesignModle::onClickedSendMessage()
{
	auto row = getCurrentSelectedIndex();
	auto text = ui.cEditForSend->text();
	context->sendTextMessage(row, text);
	
	

	//auto text = ui.
}

void ChatServerDesignModle::onClickedAddMore()
{
}

void ChatServerDesignModle::slotNeedRefreshMessageViewer(MyClient& client, Message  msg)
{
	qDebug() << "in slot need refresh" << QThread::currentThread();
	auto row = this->getCurrentSelectedIndex();
	context->refreshMessages(ui.cMessageHistory, row);
	//auto cSel = context->getClient(row);
	//auto cSel = context->getClients()->findClient(getCurrentSelectedIndex());
	
}

void ChatServerDesignModle::onChangeedServerStat()
{
	if (context->serverIsListening()) {
		context->stopServer();
		ui.cActionServerState->setChecked(false);
		ui.cToolBarServerState->setCheckable(false);

	}
	else {
		context->startServer();
		ui.cActionServerState->setChecked(true);
		ui.cToolBarServerState->setCheckable(true);
	}
}
