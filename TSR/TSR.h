#ifndef TSR_H
#define TSR_H

#include <QThread>
#include <QMutex>
#include <opencv2/opencv.hpp>

typedef struct {
	enum {Idle, ReadImg, Test} ProcessStep;
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
	void A(int k);
	cv::Mat img;
};

#endif
