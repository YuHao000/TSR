#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <opencv2\opencv.hpp>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

class ImageViewer : public QWidget {
	Q_OBJECT
public:
	ImageViewer(QWidget * parent = 0);
	void setPic(int index, const cv::Mat pic);

protected:
	void paintEvent(QPaintEvent *event);

private:
	QPixmap cvMatToQPixmap(const cv::Mat &inMat);

	int NumPixmap;
	QPixmap mPixmap[4];

};



#endif
