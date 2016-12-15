#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget * parent) :
	QWidget(parent) {
	NumPixmap = 0;
	for (int i = 0; i < 4; i++) {
		mPixmap[i] = QPixmap();
	}
}

void ImageViewer::paintEvent(QPaintEvent *event) {
	QWidget::paintEvent(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	switch (NumPixmap) {
	case 1:
		painter.drawPixmap(QPoint(0, 0), mPixmap[0].scaled(this->width(), this->height()));
		break;

	case 2:
		painter.drawPixmap(QPoint(0, 0), mPixmap[0].scaled(this->width() / 2, this->height()));
		painter.drawPixmap(QPoint(this->width() / 2, 0), mPixmap[1].scaled(this->width() / 2, this->height()));
		break;

	case 4:
		painter.drawPixmap(QPoint(this->width() / 2, this->height() / 2), mPixmap[3].scaled(this->width() / 2, this->height() / 2));

	case 3:
		painter.drawPixmap(QPoint(0, 0), mPixmap[0].scaled(this->width() / 2, this->height() / 2));
		painter.drawPixmap(QPoint(this->width() / 2, 0), mPixmap[1].scaled(this->width() / 2, this->height() / 2));
		painter.drawPixmap(QPoint(0, this->height() / 2), mPixmap[2].scaled(this->width() / 2, this->height() / 2));
		break;

	default:
		break;
	}

	
}

void ImageViewer::setPic(int index, const cv::Mat pic) {
	mPixmap[index] = cvMatToQPixmap(pic);
	if (index + 1 > NumPixmap)
		NumPixmap = index + 1;
	this->update();
}

QPixmap ImageViewer::cvMatToQPixmap(const cv::Mat &inMat) {
	switch (inMat.type())
	{
		// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_ARGB32);
		CvSize aaa = CvSize(56, 78);
		return QPixmap::fromImage(image);
	}

	// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_RGB888);

		return QPixmap::fromImage(image.rgbSwapped());
	}

	// 8-bit, 1 channel
	case CV_8UC1:
	{
		static QVector<QRgb>  sColorTable(256);

		// only create our color table the first time
		if (sColorTable.isEmpty())
		{
			for (int i = 0; i < 256; ++i)
			{
				sColorTable[i] = qRgb(i, i, i);
			}
		}

		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_Indexed8);

		image.setColorTable(sColorTable);

		return QPixmap::fromImage(image);
	}

	default:
		break;
	}

	return QPixmap();
}
