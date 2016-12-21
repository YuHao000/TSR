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
			
			GetROIImage();
			SaturationEnhance();
			startTime = getTickCount();
			Binary();
			Shape();
			endTime = getTickCount();
			//HistogramEqualize();
			OutputROIImage();	

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

// 裁剪输入图像，为了处理方便，没有严格使用输入ROI
// 实际处理的图像范围会大于指定范围
void TSR::GetROIImage() {
	if (currentState.DetectAreaEnabled)
		img = img(Rect(0, 0, img.cols, img.rows * currentState.DetectArea[1]));
}

// 生成输出ROI图像
// 将多处理那一块区域填充为黑色
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
			data[j] = 0;
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
	if (currentState.Histogram && currentState.EnhanceEnabled)
		equalizeHist(img, img);
}

// 二值化
void TSR::Binary() {
	vector<Mat> channels;
	Mat hsvimg(img.rows, img.cols, CV_8UC3);
	vector<Mat> hsvchannels;

	switch (currentState.BinaryMethod)
	{
	// HSV
	case 0:
		cvtColor(img, img, CV_BGR2HSV);
		split(img, channels);
		img = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (int i = 0; i < img.rows; i++) {
			uchar * H = channels[0].ptr<uchar>(i);
			uchar * S = channels[1].ptr<uchar>(i);
			uchar * V = channels[2].ptr<uchar>(i);
			uchar * data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++) {
				if (currentState.BinaryHmin < 0) {
					if (H[j] > currentState.BinaryHmax / 2 && H[j] < (currentState.BinaryHmin + 360) / 2)
						continue;
				}
				else if (H[j] < currentState.BinaryHmin / 2 || H[j] > currentState.BinaryHmax / 2) {
					continue;
				}

				if (S[j] < currentState.BinarySmin)
					continue;

				if (V[j] < currentState.BinaryVmin)
					continue;

				data[j] = 255;
			}
		}
		break;

	// RGB
	case 1:
		split(img, channels);
		img = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (int i = 0; i < img.rows; i++) {
			uchar * B = channels[0].ptr<uchar>(i);
			uchar * G = channels[1].ptr<uchar>(i);
			uchar * R = channels[2].ptr<uchar>(i);
			uchar * data = img.ptr<uchar>(i);
			
			for (int j = 0; j < img.cols; j++) {
				if (currentState.SignType == 0) {
					if (R[j] - B[j] > currentState.BinaryRed && R[j] - G[j] > currentState.BinaryRed)
						data[j] = 255;
				}
				else if (currentState.SignType == 1) {
					if (R[j] - B[j] > currentState.BinaryYellow && G[j] - B[j] > currentState.BinaryYellow)
						data[j] = 255;
				}
			}
		}
		break;

	// SVF
	case 2:
		split(img, channels);
		img = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (int i = 0; i < img.rows; i++) {
			uchar * B = channels[0].ptr<uchar>(i);
			uchar * G = channels[1].ptr<uchar>(i);
			uchar * R = channels[2].ptr<uchar>(i);
			uchar * data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++) {
				int tmp = abs(R[j] - G[j]) + abs(G[j] - B[j]) + abs(B[j] - R[j]);
				if (tmp >= 3 * currentState.BinaryD)
					data[j] = 255;
			}
		}
		break;

	// Mixed Method
	// 1. 改进SVF算法，加快其运算速度
	// 2. 增加H分量判断
	case 3:
		cvtColor(img, hsvimg, CV_BGR2HSV);
		split(img, channels);
		split(hsvimg, hsvchannels);
		img = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (int i = 0; i < img.rows; i++) {
			uchar * B = channels[0].ptr<uchar>(i);
			uchar * G = channels[1].ptr<uchar>(i);
			uchar * R = channels[2].ptr<uchar>(i);
			uchar * H = hsvchannels[0].ptr<uchar>(i);
			uchar * data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++) {
				int tmp;
				if (B[j] < G[j])
					tmp = R[j] - B[j];
				else
					tmp = R[j] - G[j];
				if (tmp >= 1.5 * currentState.BinaryD) {
					if (currentState.BinaryHmin < 0) {
						if (H[j] > currentState.BinaryHmax / 2 && H[j] < (currentState.BinaryHmin + 360) / 2)
							continue;
					}
					else if (H[j] < currentState.BinaryHmin / 2 || H[j] > currentState.BinaryHmax / 2) {
						continue;
					}
					data[j] = 255;
				}
			}
		}
		break;

	default:
		break;
	}

	// 形态学后处理
	if (currentState.BinaryPost) {
		Mat elementDilate = getStructuringElement(MORPH_RECT, 
			Size(2 * currentState.BinaryDilate + 1, 2 * currentState.BinaryDilate + 1));
		Mat elementEorde = getStructuringElement(MORPH_RECT,
			Size(2 * currentState.BinaryErode + 1, 2 * currentState.BinaryErode + 1));

		dilate(img, img, elementDilate);
		erode(img, img, elementEorde);
	}
}

// 形状检测
void TSR::Shape() {
	vector<Vec3f> circles;
	vector<Point> points;
	vector<Point> finalpoints;

	int MinWidth = img.cols / 100;
	int MaxWidth = img.cols / 7;

	switch (currentState.ShapeMethod) {
	// Hough
	case 0:
		HoughCircles(img, circles, HOUGH_GRADIENT, 1, 50, currentState.HoughP1, currentState.HoughP2);
		break;

	// Quick Pattern
	case 1:
		// 类似水平投影法，每行单独处理
		for (int i = 0; i < img.rows; i++) {
			uchar * data = img.ptr<uchar>(i);
			int start = 0, end = 0;
			for (int j = 1; j < img.cols; j++) {
				if (data[j - 1] > data[j]) {
					start = j;
				}
				else if (data[j - 1] < data[j]) {
					end = j;
					if (start > 0) {
						if (end - start > MinWidth && end- start < MaxWidth)
							points.push_back(Point(start + (end - start) / 2, i));
					}
				}
			}
		}

		if (!img.isContinuous())
			return;

		for (int k = 0; k < points.size(); k++) {
			int x0 = points[k].x;
			int y0 = points[k].y;
			uchar * pix = img.ptr<uchar>(y0) + x0;

			vector<int> r(16);

			r[0] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (x0 + i >= img.cols) {
					break;
				}

				if (pix[i] == 255) {
					r[0] = 1000 * i;
					break;
				}
			}

			r[1] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (x0 - i < 0) {
					break;
				}

				if (pix[-i] == 255) {
					r[1] = 1000 * i;
					break;
				}
			}

			r[2] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 + i >= img.rows) {
					break;
				}

				if (*(pix + i * img.cols) == 255) {
					r[2] = 1000 * i;
					break;
				}
			}

			r[3] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 - i < 0) {
					break;
				}

				if (*(pix - i * img.cols) == 255) {
					r[3] = 1000 * i;
					break;
				}
			}

			r[4] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 + i >= img.rows || x0 + i >= img.cols) {
					break;
				}

				if (*(pix + i * img.cols + i) == 255) {
					r[4] = 1414 * i;
					break;
				}
			}

			r[5] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 + i >= img.rows || x0 - i < 0) {
					break;
				}

				if (*(pix + i * img.cols - i) == 255) {
					r[5] = 1414 * i;
					break;
				}
			}

			r[6] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 - i < 0 || x0 + i >= img.cols) {
					break;
				}

				if (*(pix - i * img.cols + i) == 255) {
					r[6] = 1414 * i;
					break;
				}
			}

			r[7] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 - i < 0 || x0 - i < 0) {
					break;
				}

				if (*(pix - i * img.cols - i) == 255) {
					r[7] = 1414 * i;
					break;
				}
			}

			r[8] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 + i >= img.rows || x0 + 2 * i >= img.cols) {
					break;
				}

				if (*(pix + i * img.cols + 2 * i) == 255) {
					r[8] = 2236 * i;
					break;
				}
			}

			r[9] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 + 2 * i >= img.rows || x0 + i >= img.cols) {
					break;
				}

				if (*(pix + 2 * i * img.cols + i) == 255) {
					r[9] = 2236 * i;
					break;
				}
			}

			r[10] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 + i >= img.rows || x0 - 2 * i < 0) {
					break;
				}

				if (*(pix + i * img.cols - 2 * i) == 255) {
					r[10] = 2236 * i;
					break;
				}
			}

			r[11] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 + 2 * i >= img.rows || x0 - i < 0) {
					break;
				}

				if (*(pix + 2 * i * img.cols - i) == 255) {
					r[11] = 2236 * i;
					break;
				}
			}

			r[12] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 - i < 0 || x0 + 2 * i >= img.cols) {
					break;
				}

				if (*(pix - i * img.cols + 2 * i) == 255) {
					r[12] = 2236 * i;
					break;
				}
			}

			r[13] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 - 2 * i < 0 || x0 + i >= img.cols) {
					break;
				}

				if (*(pix - 2 * i * img.cols + i) == 255) {
					r[13] = 2236 * i;
					break;
				}
			}

			r[14] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 - i < 0 || x0 - 2 * i < 0) {
					break;
				}

				if (*(pix - i * img.cols - 2 * i) == 255) {
					r[14] = 2236 * i;
					break;
				}
			}

			r[15] = 0;
			for (int i = 0; i < MaxWidth / 2; i++) {
				if (y0 - 2 * i < 0 || x0 - i < 0) {
					break;
				}

				if (*(pix - 2 * i * img.cols - i) == 255) {
					r[15] = 2236 * i;
					break;
				}
			}


			int zeros = 0;
			int sumr = 0;
			for (int i = 0; i < r.size(); i++) {
				sumr += r[i];
				if (r[i] == 0) {
					zeros++;
				}
			}

			if (zeros > 1)
				continue;

			bool isPoint = true;
			sumr = sumr / (r.size() - zeros);
			for (int i = 0; i < r.size(); i++) {
				if (r[i] == 0)
					continue;

				if (r[i] - sumr > sumr / 4 || sumr - r[i] > sumr / 4) {
					isPoint = false;
					break;
				}
			}

			if (isPoint) {
				for (auto it = finalpoints.begin(); it != finalpoints.end(); it++) {
					if ((points[k].x - it->x) * (points[k].x - it->x) + (points[k].y - it->y) * (points[k].y - it->y)
						< (long long)sumr * (long long)sumr / 1000000) {
						isPoint = false;
						break;
					}
				}
				if (isPoint) {
					finalpoints.push_back(points[k]);
					circles.push_back(Vec3f(points[k].x, points[k].y, (float)sumr / 1000));
				}
					
			}

		}



		break;
	}

	TSRResultLock.lock();
	TSRResult.circles = circles;
	TSRResult.points = finalpoints;
	TSRResult.progressPoints = points;
	TSRResultLock.unlock();
}