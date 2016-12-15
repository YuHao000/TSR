#include "TSR.h"

using namespace cv;

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
		TSRParamLock.unlock();

		switch (currentState.ProcessStep) {
		case currentState.Idle:
			sleep(1);
			break;

		case currentState.ReadImg:
			ImgReadLock.lock();
			img = ImgRead.clone();
			ImgReadLock.unlock();

			TSRParamLock.lock();
			TSRParam.ProcessStep = TSRParam.Test;
			TSRParamLock.unlock();
			break;

		case currentState.Test:
			startTime = getTickCount();
			A(currentState.k);
			endTime = getTickCount();

			TSRResultLock.lock();
			TSRResult.ElapseTime = 1000.0*(endTime - startTime) / getTickFrequency();
			TSRResultLock.unlock();

			ImgOutLock.lock();
			ImgOut = img.clone();
			ImgOutLock.unlock();

			TSRParamLock.lock();
			TSRParam.ProcessStep = TSRParam.Idle;
			TSRParamLock.unlock();

			emit ImageReady();
			break;
		}
	}
	

}

void TSR::A(int k) {
	medianBlur(img, img, k);
}