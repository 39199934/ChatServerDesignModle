#include "ChatServerDesignModle.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChatServerDesignModle w;
	w.show();
	return a.exec();
}
