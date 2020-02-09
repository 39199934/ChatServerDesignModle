#include "ChatServerDesignModle.h"

ChatServerDesignModle::ChatServerDesignModle(QWidget *parent)
	: QMainWindow(parent),
	server(new MyServer(this))
{
	ui.setupUi(this);
	server->listen(QHostAddress::Any, 5666);
	ui.cListView->setModel(server->clients);
	ui.tableView->setModel(server->clients);
	//auto mode = ui.cListView->selectionMode();
	auto modeSingle = QAbstractItemView::SelectionMode::SingleSelection;
	ui.cListView->setSelectionMode(modeSingle);
	ui.tableView->setSelectionMode(modeSingle);
	//ui.cListView->setSelectionMode(QAbstractItemModel::)
	server->setMessageHistoryViewer(ui.cMessageHistory);
	//connect()
	//ui.menuBar->menu
	connect(ui.cActionServerState, &QAction::triggered, this, &ChatServerDesignModle::onChangeedServerStat);
	server->start();
	ui.cActionServerState->setChecked(true);
	ui.cToolBarServerState->setCheckable(true);
	connect(ui.cBtnSend, &QPushButton::clicked, this, &ChatServerDesignModle::onClickedBtnSend);
	
}

ChatServerDesignModle::~ChatServerDesignModle()
{
	//serve
	
	delete server;
}

void ChatServerDesignModle::onClickedBtnSend()
{
	auto index = getSelectedIndex();
	if (index < 0) {
		QMessageBox::information(this,QString::fromLocal8Bit( "警告"), QString::fromLocal8Bit("没有选择客户端"));
		return;
	}
	auto text = ui.cEditForSend->text();
	auto client = server->findClientByIndex(index);
	auto textBody = new TextBody(text, "", client->clientInfo->getUuid());
	auto msg = new Message(textBody, this);
	client->sendMessage(msg);
}

int ChatServerDesignModle::getSelectedIndex()
{
	auto selectionModel = ui.cListView->selectionModel();
	auto selectedIndex = selectionModel->selectedIndexes();
	if (selectedIndex.isEmpty()) {
		return -1;
	}
	return selectedIndex[0].row();
	//return 0;
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
