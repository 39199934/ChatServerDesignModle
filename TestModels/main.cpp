#include <QtCore/QCoreApplication>
//#include <QtCore\QApplication>
#include <QtWidgets\QApplication>
#include "Window.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QApplication  a(argc.argv);
	//QApplication b;
	Window w;
	w.show();

	return a.exec();
}
