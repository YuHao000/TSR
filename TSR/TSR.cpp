#include "TSR.h"

using namespace cv;
using namespace std;

QMutex ImgReadLock, ImgOutLock, TSRParamLock, TSRResultLock;
TSRParam_t TSRParam;
TSRResult_t TSRResult;

TSR::TSR() {
	TSRParam.ProcessStep = TSRParam.Idle;
}

void TSR::run() {
	while (true) {
		TSRParamLock.lock();
		currentState = TSRParam;
		TSRParamLock.unlock();

		// 主要状态机
		switch (currentState.ProcessStep) {
		case TSRParam.Idle:
			msleep(50);
			break;

		case TSRParam.ReadImg:
			ImgReadLock.lock();
			img = ImgRead.clone();
			ImgReadLock.unlock();

			TSRParamLock.lock();
			TSRParam.ProcessStep = TSRParam.Step1;
			TSRParamLock.unlock();
			break;

		case TSRParam.Step1:
			startTime = getTickCount();
			GetROIImage();
			SaturationEnhance();
			ExtractGrayscale();
			HistogramEqualize();
			OutputROIImage();
			endTime = getTickCount();

			TSRResultLock.lock();
			TSRResult.ElapseTime = 1000.0*(endTime - startTime) / getTickFrequency();
			TSRResultLock.unlock();

			ImgOutLock.lock();
			ImgOut = img.clone();
			ImgOutLock.unlock();

			emit ImageReady();

			TSRParamLock.lock();
			TSRParam.ProcessStep = TSRParam.Idle;
			TSRParamLock.unlock();
			
			break;
		}
	}
	

}

void TSR::A(int k) {
	medianBlur(img, img, k);
}

// 裁剪输入图像，为了处理方便，没有严格使用输入ROI
// 实际处理的图像范围会大于指定范围
void TSR::GetROIImage() {
	if (currentState.DetectAreaEnabled)
		img = img(Rect(0, 0, img.cols, img.rows * currentState.DetectArea[1]));
}

// 生成输出ROI图像
// 将多处理那一块区域填充为灰色
void TSR::OutputROIImage() {
	if (!currentState.DetectAreaEnabled)
		return;

	double ROITop = currentState.DetectArea[0];
	double ROIBottom = currentState.DetectArea[1];
	double ROISide = currentState.DetectArea[2];

	int a = img.channels();
	int b = img.type();
	int cols = img.cols * (1 - ROISide / 2) * img.channels();

	for (int i = img.rows / ROIBottom * ROITop; i < img.rows; i++) {
		uchar * data = img.ptr<uchar>(i);
		for (int j = img.cols * ROISide / 2 * img.channels(); j < cols; j++) {
			data[j] = 155;
		}
	}
}

// 饱和度增强
void TSR::SaturationEnhance() {
	if (!currentState.EnhanceEnabled)
		return;

	cvtColor(img, img, CV_BGR2HSV);
	vector<Mat> channels;
	split(img, channels);
	int tmp;
	for (int i = 0; i < channels[1].rows; i++) {
		uchar * data = channels[1].ptr<uchar>(i);
		for (int j = 0; j < channels[1].cols; j++) {
			tmp = (double)data[j] * (double)currentState.Saturation / 100.0;
			if (tmp > 255)
				data[j] = 255;
			else
				data[j] = tmp;
		}
	}
	merge(channels, img);
	cvtColor(img, img, CV_HSV2BGR);
}

// 直方图均衡化
void TSR::HistogramEqualize() {
	//equalizeHist(img, img);
}

// 提取灰度图
void TSR::ExtractGrayscale() {
	if (!currentState.GrayscaleEnabled)
		return;

	vector<Mat> channels;
	switch (currentState.GrayscaleMethed)
	{
	case 0:
		break;

	// Hue分量
	case 1:
		cvtColor(img, img, CV_BGR2HSV);	
		split(img, channels);
		img = channels[1];
		break;

	default:
		break;
	}

}