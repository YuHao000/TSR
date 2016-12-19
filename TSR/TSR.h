#ifndef TSR_H
#define TSR_H

#include <QThread>
#include <QMutex>
#include <opencv2/opencv.hpp>

#define COLOR_RED cv::Scalar(0, 0, 255)
#define COLOR_GRAY cv::Scalar(155, 155, 155)

typedef struct {
	enum {Idle, ReadImg, Step1, Step2, Step3} ProcessStep;

	// 类型
	int SignType;

	// 检测区域设置
	bool DetectAreaEnabled;
	double DetectArea[3];
	int DetectDiv;

	// 图像增强设置
	bool EnhanceEnabled;
	int Saturation;
	bool Histogram;

	// 二值化设置
	int BinaryMethod;
	int BinaryHmin, BinaryHmax, BinarySmin, BinaryVmin;
	int BinaryRed, BinaryYellow;
	int BinaryD;
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
	TSRParam_t currentState;
	int64 startTime;
	int64 endTime;
	cv::Mat img;

	void GetROIImage();
	void OutputROIImage();
	void SaturationEnhance();
	void HistogramEqualize();
	void Binary();
};

#endif
