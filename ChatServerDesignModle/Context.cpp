#include "Context.h"

Context::Context(QObject *parent)
	: QObject(parent)
{
}

Context::~Context()
{
}

Context* Context::getConText(QObject * parent)
{
	if (context == nullptr) {
		context = new Context(parent);
		clients = new Clients(parent);
		serverSetting = new ServerSetting(parent);
		
	}
	return context;
}
