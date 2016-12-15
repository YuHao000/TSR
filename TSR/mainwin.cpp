#include "mainwin.h"

#ifdef  _MSC_VER
#pragma execution_character_set("utf-8")
#endif

using namespace cv;
using namespace std;

TSR myTSR;

Mat ImgRead;
Mat ImgOut;

MainWin::MainWin(QWidget *parent) : QMainWindow(parent){
	ui.setupUi(this);

	ui.menuBar->hide();

	ui.mainToolBar->addAction(ui.actionOpenImg);
	ui.mainToolBar->addAction(ui.actionOpenVideo);
	ui.mainToolBar->addAction(ui.actionResend);

	GetSettings();
	myTSR.start();

	// Action
	connect(ui.actionOpenImg, SIGNAL(triggered()), this, SLOT(OpenNewImg()));
	connect(ui.actionOpenVideo, SIGNAL(triggered()), this, SLOT(OpenNewVideo()));
	connect(ui.actionResend, SIGNAL(triggered()), this, SLOT(SendImage()));

	connect(ui.conScroll, SIGNAL(valueChanged(int)), this, SLOT(SendImage()));

	// Video control box
	connect(ui.btnPlay, SIGNAL(clicked()), this, SLOT(SetVideoAutoPlay()));
	connect(ui.btnNext, SIGNAL(clicked()), this, SLOT(NextFrame()));
	connect(ui.btnPrevious, SIGNAL(clicked()), this, SLOT(PreviousFrame()));
	connect(ui.ProgressBar, SIGNAL(valueChanged(int)), this, SLOT(CaptureFrame(int)));

	connect(&myTSR, SIGNAL(ImageReady()), this, SLOT(UpdateImage()));
}

// Open New Image File Slot
void MainWin::OpenNewImg() {
	// Release video capture first
	if (capture.isOpened())
		capture.release();

	// Disable Video Control Box
	ui.VideoControlBox->setEnabled(false);

	QString path = QFileDialog::getOpenFileName(this, "打开图片文件",
		"D:\\Pictures\\SJTU_pic\\sjtuvis", "图片(*.png *.jpg)");

	if (!path.isEmpty()) {
		ImgReadLock.lock();
		ImgRead = imread(UTF8ToGBK(path.toStdString().data()));
		((ImageViewer *)ui.PicArea)->setPic(0, ImgRead);
		ImgReadLock.unlock();
		
		SendImage();
	}
}

// Open New Video File Slot
void MainWin::OpenNewVideo() {
	// Release video capture first
	if (capture.isOpened())
		capture.release();

	// Disable Video Control Box First
	ui.VideoControlBox->setEnabled(false);

	QString path = QFileDialog::getOpenFileName(this, "打开视频文件",
		"D:\\CSC\\OpenCV\\Record", "视频(*.mov *.mp4 *.avi)");

	if (!path.isEmpty()) {
		capture.open(UTF8ToGBK(path.toStdString().data()));
		ui.VideoControlBox->setEnabled(true);
		// Reset autoplay button
		AutoPlay = false;
		ui.btnPlay->setText("播放");
		ui.ProgressBar->setMaximum(capture.get(CAP_PROP_FRAME_COUNT) - 1);
		ui.ProgressBar->setValue(0);
		// Display first frame
		CaptureFrame(0);
	}
}

// Send current image to TSR Algorithm module
void MainWin::SendImage() {
	TSRParamLock.lock();
	TSRParam.DetectAreaEnable = ui.checkDetectArea->isChecked();
	TSRParam.DetectArea[0] = ui.edtDetectTop->value();
	TSRParam.DetectArea[1] = ui.edtDetectBottom->value();
	TSRParam.DetectArea[2] = ui.edtDetectSide->value();
	TSRParam.DetectDiv = ui.comboDetectDiv->currentIndex();
	TSRParam.k = 2 * ui.conScroll->value() - 1;
	TSRParam.ProcessStep = TSRParam.ReadImg;
	TSRParamLock.unlock();
}

// TSR Algorithm callback slot
// Image Processing Finished
void MainWin::UpdateImage() {
	ImgOutLock.lock();
	((ImageViewer *)ui.PicArea)->setPic(1, ImgOut);
	ImgOutLock.unlock();

	TSRResultLock.lock();
	ui.label->setText(QString::number(TSRResult.ElapseTime));
	TSRResultLock.unlock();

	if (capture.isOpened() && AutoPlay) {
		NextFrame();
	}
}

// Captuer Previous Frame
void MainWin::PreviousFrame() {
	ui.ProgressBar->setValue(ui.ProgressBar->value() - 1);
	CaptureFrame(ui.ProgressBar->value());
}

// Captuer Next Frame
void MainWin::NextFrame() {
	ui.ProgressBar->setValue(ui.ProgressBar->value() + 1);
	CaptureFrame(ui.ProgressBar->value());
}

// Capture One Frame
void MainWin::CaptureFrame(int val) {
	if (!capture.isOpened())
		return;

	capture.set(CAP_PROP_POS_FRAMES, val);

	ImgReadLock.lock();
	capture >> ImgRead;
	if (ui.checkDetectArea->isChecked()) {
		ImgDisplay = ImgRead.clone();
		double x1 = ImgDisplay.cols * ui.edtDetectSide->value() / 2;
		double x2 = ImgDisplay.cols - x1;
		double y1 = ImgDisplay.rows * ui.edtDetectTop->value();
		double y2 = ImgDisplay.rows * ui.edtDetectBottom->value();

		line(ImgDisplay, Point(0 , y2), Point(x1, y2), COLOR_RED, 2);
		line(ImgDisplay, Point(x1, y2), Point(x1, y1), COLOR_RED, 2);
		line(ImgDisplay, Point(x1, y1), Point(x2, y1), COLOR_RED, 2);
		line(ImgDisplay, Point(x2, y1), Point(x2, y2), COLOR_RED, 2);
		line(ImgDisplay, Point(x2, y2), Point(ImgDisplay.cols, y2), COLOR_RED, 2);

		((ImageViewer *)ui.PicArea)->setPic(0, ImgDisplay);
	}
	else {
		((ImageViewer *)ui.PicArea)->setPic(0, ImgRead);
	}
	
	ImgReadLock.unlock();

	SendImage();

	ui.statusBar->showMessage(QString::number(val) + " / " + QString::number(ui.ProgressBar->maximum()));
}

// Auto Play Button Slot
void MainWin::SetVideoAutoPlay() {
	if (AutoPlay) {
		AutoPlay = false;
		ui.btnPlay->setText("播放");
	}
	else {
		AutoPlay = true;
		ui.btnPlay->setText("暂停");
	}
}

string MainWin::UTF8ToGBK(const char* strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

void MainWin::GetSettings() {
	/* Get Settings */
	QSettings mySetting(QSettings::IniFormat, QSettings::UserScope, "GMF", "TSR");

	// Window
	resize(mySetting.value("WinSize", QSize(1024, 768)).toSize());
	move(mySetting.value("WinPos", QPoint(0, 0)).toPoint());

	// Detect Area
	ui.checkDetectArea->setChecked(mySetting.value("EnableDetectArea", false).toBool());
	ui.edtDetectTop->setValue(mySetting.value("DetectTop", 0.00).toDouble());
	ui.edtDetectBottom->setValue(mySetting.value("DetectBottom", 0.00).toDouble());
	ui.edtDetectSide->setValue(mySetting.value("DetectSide", 0.00).toDouble());
	ui.comboDetectDiv->setCurrentIndex(mySetting.value("DetectDiv", 0).toInt());
	ui.edtDetectTop->setEnabled(ui.checkDetectArea->isChecked());
	ui.edtDetectBottom->setEnabled(ui.checkDetectArea->isChecked());
	ui.edtDetectSide->setEnabled(ui.checkDetectArea->isChecked());
	ui.comboDetectDiv->setEnabled(ui.checkDetectArea->isChecked());
}

void MainWin::closeEvent(QCloseEvent *event) {
	if (capture.isOpened())
		capture.release();

	/* Save program settings */
	QSettings mySetting(QSettings::IniFormat, QSettings::UserScope, "GMF", "TSR");
	// Window
	mySetting.setValue("WinSize", size());
	mySetting.setValue("WinPos", pos());
	// Detect Area
	mySetting.setValue("EnableDetectArea", ui.checkDetectArea->isChecked());
	mySetting.setValue("DetectTop", ui.edtDetectTop->value());
	mySetting.setValue("DetectSide", ui.edtDetectSide->value());
	mySetting.setValue("DetectBottom", ui.edtDetectBottom->value());
	mySetting.setValue("DetectDiv", ui.comboDetectDiv->currentIndex());
}

