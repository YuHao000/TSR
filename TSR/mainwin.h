#ifndef MAINWIN_H
#define MAINWIN_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QMutex>
#include <QTextCodec>
#include <windows.h>
#include <string>
#include "ui_mainwin.h"
#include "ImageViewer.h"
#include "TSR.h"


class MainWin : public QMainWindow
{
	Q_OBJECT

public:
	MainWin(QWidget *parent = 0);
	~MainWin();

private:
	Ui::MainWinClass ui;
	cv::VideoCapture capture;
	bool AutoPlay = false;

	std::string UTF8ToGBK(const char* strUTF8);

private slots:
	void OpenNewImg();
	void OpenNewVideo();
	void ChangeCon(int value);
	void UpdateImage();
	void SetVideoAutoPlay();
	void NextFrame();
	void PreviousFrame();
	void CaptureFrame(int val);
};



#endif // MAINWIN_H
