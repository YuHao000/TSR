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

	Binaryboxs.push_back(ui.boxBinaryHSV);
	Binaryboxs.push_back(ui.boxBinaryRGB);
	Binaryboxs.push_back(ui.boxBinarySVF);

	GetSettings();
	myTSR.start();

	// Action
	connect(ui.actionOpenImg, SIGNAL(triggered()), this, SLOT(OpenNewImg()));
	connect(ui.actionOpenVideo, SIGNAL(triggered()), this, SLOT(OpenNewVideo()));
	connect(ui.actionResend, SIGNAL(triggered()), this, SLOT(SendImage()));

	connect(&myTSR, SIGNAL(ImageReady()), this, SLOT(UpdateImage()));

	// Video control box
	connect(ui.btnPlay, SIGNAL(clicked()), this, SLOT(SetVideoAutoPlay()));
	connect(ui.btnNext, SIGNAL(clicked()), this, SLOT(NextFrame()));
	connect(ui.btnPrevious, SIGNAL(clicked()), this, SLOT(PreviousFrame()));
	connect(ui.ProgressBar, SIGNAL(valueChanged(int)), this, SLOT(CaptureFrame(int)));

	//// 检测区域
	//connect(ui.boxDetectArea, SIGNAL(toggled(bool)), this, SLOT(SendImage()));
	//connect(ui.edtDetectTop, SIGNAL(valueChanged(double)), this, SLOT(SendImage()));
	//connect(ui.edtDetectBottom, SIGNAL(valueChanged(double)), this, SLOT(SendImage()));
	//connect(ui.edtDetectSide, SIGNAL(valueChanged(double)), this, SLOT(SendImage()));
	//connect(ui.comboDetectDiv, SIGNAL(currentIndexChanged(int)), this, SLOT(SendImage()));

	//// 图像增强
	//connect(ui.boxEnhance, SIGNAL(toggled(bool)), this, SLOT(SendImage()));
	//connect(ui.sliderSatur, SIGNAL(valueChanged(int)), this, SLOT(SendImage()));
	//connect(ui.checkHistogram, SIGNAL(toggled(bool)), this, SLOT(SendImage()));

	//// 二值化
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
	if (ImgRead.rows == 0 || ImgRead.cols == 0)
		return;

	TSRParamLock.lock();

	TSRParam.DetectAreaEnabled = ui.boxDetectArea->isChecked();
	TSRParam.DetectArea[0] = ui.edtDetectTop->value();
	TSRParam.DetectArea[1] = ui.edtDetectBottom->value();
	TSRParam.DetectArea[2] = ui.edtDetectSide->value();
	TSRParam.DetectDiv = ui.comboDetectDiv->currentIndex();

	TSRParam.EnhanceEnabled = ui.boxEnhance->isChecked();
	TSRParam.Saturation = ui.sliderSatur->value();
	TSRParam.Histogram = ui.checkHistogram->isChecked() && ui.checkHistogram->isEnabled();

	TSRParam.BinaryMethod = GetBoxMethod(Binaryboxs);
	TSRParam.BinaryHmin = ui.edtBinaryHmin->value();
	TSRParam.BinaryHmax = ui.edtBinaryHmax->value();
	TSRParam.BinarySmin = ui.edtBinarySmin->value();
	TSRParam.BinaryVmin = ui.edtBinaryVmin->value();
	TSRParam.BinaryRmin = ui.edtBinaryRmin->value();
	TSRParam.BinaryRmax = ui.edtBinaryRmax->value();
	TSRParam.BinaryGmin = ui.edtBinaryGmin->value();
	TSRParam.BinaryGmax = ui.edtBinaryGmax->value();
	TSRParam.BinaryBmin = ui.edtBinaryBmin->value();
	TSRParam.BinaryBmax = ui.edtBinaryBmax->value();
	TSRParam.BinaryD = ui.edtBinaryD->value();

	TSRParam.ProcessStep = TSRParam.ReadImg;
	TSRParamLock.unlock();
}

// TSR Algorithm callback slot
// Image Processing Finished
void MainWin::UpdateImage() {
	ImgReadLock.lock();
	ImgOutLock.lock();

	((ImageViewer *)ui.PicArea)->setPic(1, ImgOut);

	Mat tmp(ImgOut.rows, ImgOut.cols, CV_8UC3, Scalar(0,0,0));
	ImgRead(Rect(0,0,ImgOut.cols,ImgOut.rows)).copyTo(tmp, ImgOut);
	((ImageViewer *)ui.PicArea)->setPic(2, tmp);

	ImgOutLock.unlock();
	ImgReadLock.unlock();

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
	if (ui.boxDetectArea->isChecked()) {
		ImgDisplay = ImgRead.clone();
		double x1 = ImgDisplay.cols * ui.edtDetectSide->value() / 2;
		double x2 = ImgDisplay.cols - x1;
		double y1 = ImgDisplay.rows * ui.edtDetectTop->value();
		double y2 = ImgDisplay.rows * ui.edtDetectBottom->value();

		line(ImgDisplay, Point(0 , y2), Point(x1, y2), COLOR_RED, 2);
		line(ImgDisplay, Point(x1, y2), Point(x1, y1), COLOR_RED, 4);
		line(ImgDisplay, Point(x1, y1), Point(x2, y1), COLOR_RED, 2);
		line(ImgDisplay, Point(x2, y1), Point(x2, y2), COLOR_RED, 4);
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
	ui.boxDetectArea->setChecked(mySetting.value("DetectAreaEnabled", false).toBool());
	ui.edtDetectTop->setValue(mySetting.value("DetectTop", 0.00).toDouble());
	ui.edtDetectBottom->setValue(mySetting.value("DetectBottom", 0.00).toDouble());
	ui.edtDetectSide->setValue(mySetting.value("DetectSide", 0.00).toDouble());
	ui.comboDetectDiv->setCurrentIndex(mySetting.value("DetectDiv", 0).toInt());

	// Image Enhancement
	ui.boxEnhance->setChecked(mySetting.value("EnhanceEnabled", false).toBool());
	ui.sliderSatur->setValue(mySetting.value("Saturation", 100).toInt());
	ui.checkHistogram->setChecked(mySetting.value("Histogram", false).toBool());

	// Binaryzation
	SetBoxMethod(Binaryboxs, mySetting.value("BinaryMethod", 0).toInt());
	ui.edtBinaryHmin->setValue(mySetting.value("BinaryHmin", 0).toInt());
	ui.edtBinaryHmax->setValue(mySetting.value("BinaryHmax", 0).toInt());
	ui.edtBinarySmin->setValue(mySetting.value("BinarySmin", 0).toInt());
	ui.edtBinaryVmin->setValue(mySetting.value("BinaryVmin", 0).toInt());
	ui.edtBinaryRmin->setValue(mySetting.value("BinaryRmin", 0).toInt());
	ui.edtBinaryRmax->setValue(mySetting.value("BinaryRmax", 0).toInt());
	ui.edtBinaryGmin->setValue(mySetting.value("BinaryGmin", 0).toInt());
	ui.edtBinaryGmax->setValue(mySetting.value("BinaryGmax", 0).toInt());
	ui.edtBinaryBmin->setValue(mySetting.value("BinaryBmin", 0).toInt());
	ui.edtBinaryBmax->setValue(mySetting.value("BinaryBmax", 0).toInt());
	ui.edtBinaryD->setValue(mySetting.value("BinaryD", 0).toInt());
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
	mySetting.setValue("DetectAreaEnabled", ui.boxDetectArea->isChecked());
	mySetting.setValue("DetectTop", ui.edtDetectTop->value());
	mySetting.setValue("DetectSide", ui.edtDetectSide->value());
	mySetting.setValue("DetectBottom", ui.edtDetectBottom->value());
	mySetting.setValue("DetectDiv", ui.comboDetectDiv->currentIndex());

	// Image Enhancement
	mySetting.setValue("EnhanceEnabled", ui.boxEnhance->isChecked());
	mySetting.setValue("Saturation", ui.sliderSatur->value());
	mySetting.setValue("Histogram", ui.checkHistogram->isChecked());

	// Binaryzation
	mySetting.setValue("BinaryMethod", GetBoxMethod(Binaryboxs));
	mySetting.setValue("BinaryHmin", ui.edtBinaryHmin->value());
	mySetting.setValue("BinaryHmax", ui.edtBinaryHmax->value());
	mySetting.setValue("BinarySmin", ui.edtBinarySmin->value());
	mySetting.setValue("BinaryVmin", ui.edtBinaryVmin->value());
	mySetting.setValue("BinaryRmin", ui.edtBinaryRmin->value());
	mySetting.setValue("BinaryRmax", ui.edtBinaryRmax->value());
	mySetting.setValue("BinaryGmin", ui.edtBinaryGmin->value());
	mySetting.setValue("BinaryGmax", ui.edtBinaryGmax->value());
	mySetting.setValue("BinaryBmin", ui.edtBinaryBmin->value());
	mySetting.setValue("BinaryBmax", ui.edtBinaryBmax->value());
	mySetting.setValue("BinaryD", ui.edtBinaryD->value());
}

// 读取单选按钮组的设置
int MainWin::GetRadioMethod(std::vector<QRadioButton *> radios) {
	for (auto it = radios.begin(); it != radios.end(); it++) {
		if ((*it)->isChecked())
			return it - radios.begin();
	}

	return -1;
}

// 设置按钮组的状态
void MainWin::SetRadioMethod(std::vector<QRadioButton *> radios, int val) {
	radios[val]->setChecked(true);
}

// 读取GroupBox组的设置
int MainWin::GetBoxMethod(std::vector<QGroupBox *> boxs) {
	for (auto it = boxs.begin(); it != boxs.end(); it++) {
		if ((*it)->isChecked())
			return it - boxs.begin();
	}

	return -1;
}

// 设置GroupBox组的状态
void MainWin::SetBoxMethod(std::vector<QGroupBox *> boxs, int val) {
	for (int i = 0; i < boxs.size(); i++) {
		if (i == val) {
			boxs[i]->setChecked(true);
		}
		else {
			boxs[i]->setChecked(false);
		}
	}
}


