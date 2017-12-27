#include "mainwin.h"

#ifdef  _MSC_VER
#pragma execution_character_set("utf-8")
#endif

using namespace cv;
using namespace std;

TSR myTSR;

Mat ImgRead;
Mat ImgOut;

// Note: 
// 增加一个新控件有以下几个地方需要添加代码：
// 1. closeEvent()中保存设置;
// 2. GetSetting()中读取设置;
// 3. TSRParam_t结构体中增加数据成员;
// 4. SendImage()中为TSRParam赋值

MainWin::MainWin(QWidget *parent) : QMainWindow(parent){
	ui.setupUi(this);

	ui.menuBar->hide();

	ui.mainToolBar->addAction(ui.actionOpenImg);
	ui.mainToolBar->addAction(ui.actionOpenVideo);
	ui.mainToolBar->addAction(ui.actionSaveImage);
	ui.mainToolBar->addAction(ui.actionResend);

	Binaryboxs.push_back(ui.boxBinaryHSV);
	Binaryboxs.push_back(ui.boxBinaryRGB);
	Binaryboxs.push_back(ui.boxBinarySVF);
	Binaryboxs.push_back(ui.boxBinaryMixed);

	Shapeboxs.push_back(ui.boxShapeHoughCircle);
	Shapeboxs.push_back(ui.boxShpaePatternCircle);
	Shapeboxs.push_back(ui.boxShapeTriangle);

	GetSettings();
	myTSR.start();

	// Action
	connect(ui.actionOpenImg, SIGNAL(triggered()), this, SLOT(OpenNewImg()));
	connect(ui.actionOpenVideo, SIGNAL(triggered()), this, SLOT(OpenNewVideo()));
	connect(ui.actionResend, SIGNAL(triggered()), this, SLOT(SendImage()));
	connect(ui.actionSaveImage, SIGNAL(triggered()), this, SLOT(SaveImage()));

	connect(&myTSR, SIGNAL(ImageReady()), this, SLOT(UpdateImage()));

	// Video control box
	connect(ui.btnPlay, SIGNAL(clicked()), this, SLOT(SetVideoAutoPlay()));
	connect(ui.btnNext, SIGNAL(clicked()), this, SLOT(NextFrame()));
	connect(ui.btnPrevious, SIGNAL(clicked()), this, SLOT(PreviousFrame()));
	connect(ui.ProgressBar, SIGNAL(valueChanged(int)), this, SLOT(CaptureFrame(int)));
}

// Open New Image File Slot
void MainWin::OpenNewImg() {
	QString path = QFileDialog::getOpenFileName(this, "打开图片文件",
		"C:\\Users\\g1992\\Videos\\Img", "图片(*.png *.jpg)");

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
	QString path = QFileDialog::getOpenFileName(this, "打开视频文件",
		"C:\\Users\\g1992\\Videos\\Circle", "视频(*.mov *.mp4 *.avi *.m4v)");

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

// Save Image
void MainWin::SaveImage() {
	QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
	string str = time.toString("MMddhhmmss").toStdString(); //设置显示格式
	ImgReadLock.lock();
	imwrite(SaveImagePath + str + "_ImgRead.png", ImgRead);
	ImgReadLock.unlock();

	imwrite(SaveImagePath + str + "_ImgDisplay.png", ImgDisplay);
	imwrite(SaveImagePath + str + "_ImgDisplay2.png", ImgDisplay2);
	imwrite(SaveImagePath + str + "_ImgDisplay3.png", ImgDisplay3);

	ImgOutLock.lock();
	imwrite(SaveImagePath + str + "_ImgOut.png", ImgOut);
	ImgOutLock.unlock();
}

// Send current image to TSR Algorithm module
void MainWin::SendImage() {
	if (ImgRead.rows == 0 || ImgRead.cols == 0)
		return;

	TSRParamLock.lock();

	if (ui.radioTypeLimit->isChecked())
		TSRParam.SignType = 0;
	else
		TSRParam.SignType = 1;

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
	TSRParam.BinaryImin = ui.edtBinaryVmin->value();
	TSRParam.BinaryRed = ui.edtBinaryRed->value();
	TSRParam.BinaryYellow = ui.edtBinaryYellow->value();
	TSRParam.BinaryD = ui.edtBinaryD->value();
	TSRParam.BinaryPost = ui.boxBianryPost->isChecked();
	TSRParam.BinaryDilate = ui.edtBinaryDilate->value();
	TSRParam.BinaryErode = ui.edtBinaryErode->value();
	
	TSRParam.ShapeMethod = GetBoxMethod(Shapeboxs);
	TSRParam.HoughP1 = ui.edtHoughP1->value();
	TSRParam.HoughP2 = ui.edtHoughP2->value();
	TSRParam.ShapeVariance = ui.edtShapeVariance->value();
	TSRParam.ShapeDmin = ui.edtShapeDmin->value();
	TSRParam.ShapeDmax = ui.edtShapeDmax->value();
	TSRParam.ShapeCorner = ui.edtShapeCorner->value();

	TSRParam.ProcessStep = TSRParam.ReadImg;
	TSRParamLock.unlock();
}

// TSR Algorithm callback slot
// Image Processing Finished
void MainWin::UpdateImage() {
	Mat ResultMask = Mat(ImgOut.rows, ImgOut.cols, CV_8UC1, Scalar(0));
	ImgReadLock.lock();
	ImgOutLock.lock();

	((ImageViewer *)ui.PicArea)->setPic(1, ImgOut);
	ImgDisplay = ImgRead.clone();

	ImgReadLock.unlock();

	// 根据掩膜生成提取区域彩色图
	ImgDisplay2 = Mat(ImgOut.rows, ImgOut.cols, CV_8UC3, Scalar(0, 0, 0));
	ImgDisplay(Rect(0,0,ImgOut.cols,ImgOut.rows)).copyTo(ImgDisplay2, ImgOut);

	ImgOutLock.unlock();
	

	// 画出检测区域
	if (ui.boxDetectArea->isChecked()) {
		
		double x1 = ImgDisplay.cols * ui.edtDetectSide->value() / 2;
		double x2 = ImgDisplay.cols - x1;
		double y1 = ImgDisplay.rows * ui.edtDetectTop->value();
		double y2 = ImgDisplay.rows * ui.edtDetectBottom->value();

		line(ImgDisplay, Point(0, y2), Point(x1, y2), COLOR_RED, 2);
		line(ImgDisplay, Point(x1, y2), Point(x1, y1), COLOR_RED, 4);
		line(ImgDisplay, Point(x1, y1), Point(x2, y1), COLOR_RED, 2);
		line(ImgDisplay, Point(x2, y1), Point(x2, y2), COLOR_RED, 4);
		line(ImgDisplay, Point(x2, y2), Point(ImgDisplay.cols, y2), COLOR_RED, 2);
	}

	TSRResultLock.lock();
	//ui.label->setText(QString::number(TSRResult.ElapseTime));
	vector<Vec3f> drawCircles(TSRResult.circles);
	TSRResultLock.unlock();

	if (drawCircles.empty()) {
		ImgDisplay3 = Mat(ImgOut.rows, ImgOut.cols, CV_8UC3, Scalar(140, 92, 34));
	}
	else {
		ImgDisplay3 = Mat(ImgOut.rows, ImgOut.cols, CV_8UC3, Scalar(76, 177, 34));
	}


	// 画出Hough圆检测
	if (GetBoxMethod(Shapeboxs) == 0  || GetBoxMethod(Shapeboxs) == 1) {
		for (size_t i = 0; i < drawCircles.size(); i++) {
			Point center(cvRound(drawCircles[i][0]), cvRound(drawCircles[i][1]));
			int radius = cvRound(drawCircles[i][2]);

			circle(ImgDisplay, center, 3, Scalar(255, 0, 0), -1, 8, 0);
			circle(ImgDisplay, center, radius, Scalar(255, 0, 0), 3, 8, 0);
			circle(ResultMask, center, radius, Scalar(255), -1, 8, 0);
		}
	}
	ImgRead.copyTo(ImgDisplay3, ResultMask);

	// tmp
	vector<Point> drawPoints(TSRResult.progressPoints);
	vector<Point> finalDrawPoints(TSRResult.points);
	//if (GetBoxMethod(Shapeboxs)) {
	//	for (size_t i = 0; i < drawPoints.size(); i++) {
	//		ImgDisplay2.at<Vec3b>(drawPoints[i])[1] = 255;
	//	}

	//	for (size_t i = 0; i < finalDrawPoints.size(); i++) {
	//		circle(ImgDisplay2, finalDrawPoints[i], 3, Scalar(255, 0, 0), -1, 8, 0);
	//	}
	//}

	((ImageViewer *)ui.PicArea)->setPic(0, ImgDisplay);
	((ImageViewer *)ui.PicArea)->setPic(2, ImgDisplay2);
	((ImageViewer *)ui.PicArea)->setPic(3, ImgDisplay3);

	ui.label->setText(QString::number(drawCircles.size()));

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
	((ImageViewer *)ui.PicArea)->setPic(0, ImgRead);
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

	// Sign type
	ui.radioTypeWarning->setChecked(mySetting.value("SignType", false).toBool());

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
	ui.edtBinaryRed->setValue(mySetting.value("BinaryRed", 0).toInt());
	ui.edtBinaryYellow->setValue(mySetting.value("BinaryYellow", 0).toInt());
	ui.edtBinaryD->setValue(mySetting.value("BinaryD", 0).toInt());
	ui.boxBianryPost->setChecked(mySetting.value("BinaryPost", false).toBool());
	ui.edtBinaryDilate->setValue(mySetting.value("BinaryDilate", 0).toInt());
	ui.edtBinaryErode->setValue(mySetting.value("BinaryErode", 0).toInt());

	// Shape
	SetBoxMethod(Shapeboxs, mySetting.value("ShapeMethod", 0).toInt());
	ui.edtHoughP1->setValue(mySetting.value("HoughP1", 100).toInt());
	ui.edtHoughP2->setValue(mySetting.value("HoughP2", 100).toInt());
	ui.edtShapeVariance->setValue(mySetting.value("ShapeVariance", 0).toInt());
	ui.edtShapeDmin->setValue(mySetting.value("ShapeDmin", 0).toInt());
	ui.edtShapeDmax->setValue(mySetting.value("ShapeDmax", 0).toInt());
	ui.edtShapeCorner->setValue(mySetting.value("ShapeCorner", 0).toInt());
}

void MainWin::closeEvent(QCloseEvent *event) {
	if (capture.isOpened())
		capture.release();

	/* Save program settings */
	QSettings mySetting(QSettings::IniFormat, QSettings::UserScope, "GMF", "TSR");

	// Window
	mySetting.setValue("WinSize", size());
	mySetting.setValue("WinPos", pos());

	// Sign type
	mySetting.setValue("SignType", ui.radioTypeWarning->isChecked());

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
	mySetting.setValue("BinaryRed", ui.edtBinaryRed->value());
	mySetting.setValue("BinaryYellow", ui.edtBinaryYellow->value());
	mySetting.setValue("BinaryD", ui.edtBinaryD->value());
	mySetting.setValue("BinaryPost", ui.boxBianryPost->isChecked());
	mySetting.setValue("BinaryDilate", ui.edtBinaryDilate->value());
	mySetting.setValue("BinaryErode", ui.edtBinaryErode->value());

	// Shape
	mySetting.setValue("ShapeMethod", GetBoxMethod(Shapeboxs));
	mySetting.setValue("HoughP1", ui.edtHoughP1->value());
	mySetting.setValue("HoughP2", ui.edtHoughP2->value());
	mySetting.setValue("ShapeVariance", ui.edtShapeVariance->value());
	mySetting.setValue("ShapeDmin", ui.edtShapeDmin->value());
	mySetting.setValue("ShapeDmax", ui.edtShapeDmax->value());
	mySetting.setValue("ShapeCorner", ui.edtShapeCorner->value());
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


