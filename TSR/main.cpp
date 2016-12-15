#include "mainwin.h"
#include <QtWidgets/QApplication>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setStyle("fusion");
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	MainWin w;
	w.show();
	return a.exec();
}
