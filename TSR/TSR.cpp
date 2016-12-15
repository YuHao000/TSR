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
	TSRParam_t currentState;
	while (true) {
		TSRParamLock.lock();
		currentState = TSRParam;
		ROIEnable = TSRParam.DetectAreaEnable;
		ROITop = TSRParam.DetectArea[0];
		ROIBottom = TSRParam.DetectArea[1];
		ROISide = TSRParam.DetectArea[2];
		TSRParamLock.unlock();

		// 主要状态机
		switch (currentState.ProcessStep) {
		case currentState.Idle:
			msleep(50);
			break;

		case currentState.ReadImg:
			ImgReadLock.lock();
			img = ImgRead.clone();
			ImgReadLock.unlock();

			TSRParamLock.lock();
			TSRParam.ProcessStep = TSRParam.Step1;
			TSRParamLock.unlock();
			break;

		case currentState.Step1:
			startTime = getTickCount();
			GetROIImage();
			A(currentState.k);
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
	img = img(Rect(0, 0, img.cols, img.rows * ROIBottom));
}

// 生成输出ROI图像
// 将多处理那一块区域填充为灰色
void TSR::OutputROIImage() {
	int cols = img.cols * (1 - ROISide / 2) * img.channels();

	for (int i = img.rows * ROITop; i < img.rows; i++) {
		uchar * data = img.ptr<uchar>(i);
		for (int j = img.cols * ROISide / 2 * img.channels(); j < cols; j++) {
			data[j] = 155;
		}
	}
}