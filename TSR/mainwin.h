#ifndef MAINWIN_H
#define MAINWIN_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QMutex>
#include <QTextCodec>
#include <QSettings>
#include <QDateTime>
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

protected:
	void closeEvent(QCloseEvent * event);

private:
	Ui::MainWinClass ui;
	cv::VideoCapture capture;
	bool AutoPlay = false;
	cv::Mat ImgDisplay, ImgDisplay2, ImgDisplay3;
	const std::string SaveImagePath = "D:\\CSC\\OpenCV\\TSR\\Saved\\";


	// Widget groups
	std::vector<QGroupBox *> Binaryboxs;
	std::vector<QGroupBox *> Shapeboxs;

	std::string UTF8ToGBK(const char* strUTF8);
	void GetSettings();
	int GetRadioMethod(std::vector<QRadioButton *> radios);
	void SetRadioMethod(std::vector<QRadioButton *> radios, int val);
	int GetBoxMethod(std::vector<QGroupBox *> boxs);
	void SetBoxMethod(std::vector<QGroupBox *> boxs, int val);

private slots:
	void OpenNewImg();
	void OpenNewVideo();
	void SaveImage();
	void SendImage();
	void UpdateImage();
	void SetVideoAutoPlay();
	void NextFrame();
	void PreviousFrame();
	void CaptureFrame(int val);
};



#endif // MAINWIN_H
