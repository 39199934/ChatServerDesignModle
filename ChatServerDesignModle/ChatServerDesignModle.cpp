#include "ChatServerDesignModle.h"

ChatServerDesignModle::ChatServerDesignModle(QWidget *parent)
	: QMainWindow(parent),
	context(Context::getContext(this))
{
	
	//server = new MyServer(context, this);
	ui.setupUi(this);
	context->setMessageViewr(ui.cMessageHistory);
	//server->listen(QHostAddress::Any, 5666);
	ui.cListView->setModel(context->getClients());
	ui.tableView->setModel(context->getClients());
	//server->setMessageHistoryViewer(ui.cMessageHistory);
	//connect()
	//ui.menuBar->menu
	connect(ui.cActionServerState, &QAction::triggered, this, &ChatServerDesignModle::onChangeedServerStat);
	connect(ui.cBtnSend, &QPushButton::clicked, this, &ChatServerDesignModle::onClickedSendMessage);
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
	auto sel = ui.cListView->selectionModel();
	if (!sel->hasSelection()) {
		return -1;
	}
	
	auto row = sel->selectedIndexes()[0].row();
	
	return row;
}

void ChatServerDesignModle::onClickedSendMessage()
{
	if (context->getClients()->getCount() <= 0) {
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("对不起，没有客户端"));
		return;
	}
	auto row = getCurrentSelectedIndex();
	auto text = ui.cEditForSend->text();
	auto msg = MessageFactory::BuildTextMessage(text, row);
	if (row == -1) {
		auto rt = QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("对不起，你没有选择发送给谁，消息是否发送给所有客户端？"), QMessageBox::StandardButton::Cancel, QMessageBox::StandardButton::Apply);
		if (rt == QMessageBox::StandardButton::Apply) {
			server->sendMessageToAll(msg);
		}
		else {
			return;
		}
	}
	else {
		context->getClients()->findClient(row)->sendMessage(msg);
		ui.cEditForSend->clear();
	}
	
	

	//auto text = ui.
}

void ChatServerDesignModle::onChangeedServerStat()
{
	if (context->server->isListening()) {
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
