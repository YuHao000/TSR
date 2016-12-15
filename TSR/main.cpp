#include "mainwin.h"
#include <QtWidgets/QApplication>
#include <QSettings>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setStyle("fusion");
	QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, "./");
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	MainWin w;
	w.show();
	return a.exec();
}
