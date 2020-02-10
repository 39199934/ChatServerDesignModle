#include "Context.h"

Context::Context(QObject *parent)
	:QObject(parent),
	clients(new Clients(parent)),
	serverSetting(new ServerSetting(parent))
{
	
}

Context::~Context()
{
	
	if (serverSetting) {
		delete serverSetting;
	}
	if (clients) {
		delete clients; 
	}
	/*if (context) {
		delete context;
		//context = nullptr;
	}*/
}

Context* Context::getContext(QObject* parent)
{
	if (context == nullptr) {
		context = new Context(parent);
	}
	return context;
}
Clients* Context::getClients()
{
	/*if (clients == nullptr) {
		clients = new Clients()
	}*/
	return clients;
}
ServerSetting* Context::getServerSetting()
{
	return serverSetting;
}
void Context::setMessageViewr(QTextEdit* viewer)
{
	this->messageViewer = viewer;
}
Context* Context::context = nullptr;
