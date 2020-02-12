#include "ChatClientDesignModle.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChatClientDesignModle w;
	w.show();
	return a.exec();
}
