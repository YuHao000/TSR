#ifndef TSR_H
#define TSR_H

#include <QThread>
#include <QMutex>
#include <opencv2/opencv.hpp>

#define COLOR_RED cv::Scalar(0, 0, 255)
#define COLOR_GRAY cv::Scalar(155, 155, 155)

typedef struct {
	enum {Idle, ReadImg, Step1, Step2, Step3} ProcessStep;
	bool DetectAreaEnable;
	double DetectArea[3];
	int DetectDiv;
	int k;
}TSRParam_t;

typedef struct {
	double ElapseTime;
}TSRResult_t;

extern cv::Mat ImgRead;
extern cv::Mat ImgOut;
extern TSRParam_t TSRParam;
extern TSRResult_t TSRResult;
extern QMutex ImgReadLock, ImgOutLock, TSRParamLock, TSRResultLock;

class TSR : public QThread{
	Q_OBJECT

signals:
	void ImageReady();

public:
	TSR();

protected:
	void run();

private:
	int64 startTime;
	int64 endTime;
	cv::Mat img;
	cv::Rect ROI;

	// ROI
	bool ROIEnable;
	double ROITop, ROIBottom, ROISide;

	void A(int k);
	void GetROIImage();
	void OutputROIImage();
};

#endif
