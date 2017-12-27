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
	
	Mat hsvimg(img.rows, img.cols, CV_8UC3);
	vector<Mat> hsvchannels;

	switch (currentState.BinaryMethod)
	{
	// HSI
	case 0:
		//BGR2HSI(img, channels[0], channels[1], channels[2]);
		cvtColor(img, img, CV_BGR2HLS);
		split(img, channels);
		img = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (int i = 0; i < img.rows; i++) {
			uchar * H = channels[0].ptr<uchar>(i);
			uchar * I = channels[1].ptr<uchar>(i);
			uchar * S = channels[2].ptr<uchar>(i);
			uchar * data = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++) {
				if (currentState.BinaryHmin < 0) {
					if (2 * (int)H[j] > currentState.BinaryHmax && 2 * (int)H[j] < (currentState.BinaryHmin + 360))
						continue;
				}
				else if (2 * (int)H[j] < currentState.BinaryHmin || 2 * (int)H[j] > currentState.BinaryHmax ) {
					continue;
				}

				if (S[j] < currentState.BinarySmin)
					continue;

				if (I[j] < currentState.BinaryImin || I[j] > 210)
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
					if (currentState.BinaryRed > 30) {
						if (R[j] - B[j] > 20 && R[j] - G[j] >= 20)
							data[j] = 255;
					}
					else {
						if ((R[j] + B[j] + G[j])*0.4 <= R[j] && (R[j] + B[j] + G[j])*0.35 >= G[j])
							data[j] = 255;
					}
					//if (R[j] - B[j] > currentState.BinaryRed && R[j] - G[j] > currentState.BinaryRed)
					//if (R[j] - B[j] > currentState.BinaryRed && R[j] - G[j] > currentState.BinaryRed && (R[j]+B[j]+G[j])*0.4 < R[j] && (R[j] + B[j] + G[j])*0.35 > G[j])
					//	data[j] = 255;
				}
				else if (currentState.SignType == 1) {
					if (currentState.BinaryRed > 30) {
						if (R[j] - B[j] > 30 && G[j] - B[j] >= 30)
							data[j] = 255;
					}
					else {
						if ((R[j] + B[j] + G[j])*0.85 < R[j] + G[j])
							data[j] = 255;
					}
					//if (R[j] - B[j] > currentState.BinaryYellow && G[j] - B[j] > currentState.BinaryYellow)
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
	case 3:
		//cvtColor(img, hsvimg, CV_BGR2HSV);
		split(img, channels);
		//split(hsvimg, hsvchannels);
		img = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (int i = 0; i < img.rows; i++) {
			uchar * B = channels[0].ptr<uchar>(i);
			uchar * G = channels[1].ptr<uchar>(i);
			uchar * R = channels[2].ptr<uchar>(i);
			//uchar * H = hsvchannels[0].ptr<uchar>(i);
			uchar * data = img.ptr<uchar>(i);
			
			for (int j = 0; j < img.cols; j++) {
				int r = R[j], g = G[j], b = B[j];
				if (currentState.SignType == 0) {
					if (R[j] >= G[j] && G[j] >= B[j]) {
						if (r - g < 20) continue;
						if (r - b < 30) continue;
						if (r - 3 * g + 2 * b < 0) continue;
						if (3 * r - 2 * g - 2 * b < 0) continue;
						if (7 * r - 13 * g + 7 * b < 0) continue;
						if (r + b >= 255) {
							if (31 * r - 19 * b < 3060) continue;
							if (r + b > 420) continue;
							data[j] = 255;
						}
						else {
							if (19 * r - 31 * b < 0) continue;
							if (r + b < 40) continue;
							data[j] = 255;
						}
					}
					else if (R[j] >= B[j] && B[j] >= G[j]) {
						if (r - b < 20) continue;
						if (r - g < 30) continue;
						if (2 * r + g - 3 * b < 0) continue;
						if (3 * r - 2 * g - 2 * b < 0) continue;
						if (7 * r - 13 * g + 7 * b < 0) continue;
						if (r + g >= 255) {
							if (31 * r - 19 * g < 3060) continue;
							if (r + g > 420) continue;
							data[j] = 255;
						}
						else {
							if (19 * r - 31 * g < 0) continue;
							if (r + g < 40) continue;
							data[j] = 255;
						}
					}
					else {
						continue;
					}
				}
				else {
					if (R[j] >= G[j] && G[j] >= B[j]) {
						if (r - b < 30) continue;
						if (g - b < 30) continue;
						if (r - g < 0) continue;
						if (-7 * r + 12 * g - 5 * b < 0) continue;
						if (3 * r + 3 * g - 17 * b < 0) continue;
						if (r + b >= 255) {
							if (31 * r - 19 * b < 3060) continue;
							if (r + b > 420) continue;
							data[j] = 255;
						}
						else {
							if (19 * r - 31 * b < 0) continue;
							if (r + b < 40) continue;
							data[j] = 255;
						}
					}
					else {
						continue;
					}
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
	vector<Point> points, points2;
	vector<Point> finalpoints;


	int dx[] = { +1, +2, +1, +1, +0, -1, -1, -2, -1, -2, -1, -1, +0, +1, +1, +2 };
	int dy[] = { +0, +1, +1, +2, +1, +2, +1, +1, +0, -1, -1, -2, -1, -2, -1, -1 };
	int lcoff[] = { 100, 224, 141, 224, 100, 224, 141, 224, 100, 224, 141, 224, 100, 224, 141, 224 };
	switch (currentState.ShapeMethod) {
	// Hough
	case 0:
		HoughCircles(img, circles, HOUGH_GRADIENT, 1, currentState.HoughP1, 150, currentState.HoughP2, currentState.ShapeDmin / 2, currentState.ShapeDmax / 2);
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
						if (end - start > currentState.ShapeDmin && end- start < currentState.ShapeDmax)
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
			int zeros = 0;
			int sumr = 0;
			int avgr = 0;
			int variancer = 0;

			for (int delt = 0; delt < 16; delt++) {
				r[delt] = 0;
				for (int i = 0; i < currentState.ShapeDmax / 2; i++) {
					if (y0 + dy[delt] * i < 0 || y0 + dy[delt] * i >= img.rows
						|| x0 + dx[delt] * i < 0 || x0 + dx[delt] * i >= img.cols) {
						break;
					}

					if (*(pix + dy[delt] * i * img.cols + dx[delt] * i) == 255) {
						r[delt] = lcoff[delt] * i;
						break;
					}
				}
				if (r[delt] < 100 * currentState.ShapeDmin) {
					zeros++;
					if (zeros > 1)
						break;
				}
				else {
					sumr += r[delt];
				}
			}

			if (zeros > 1)
				continue;

			bool isPoint = true;
			avgr = sumr / (16 - zeros);
			for (int i = 0; i < 16; i++) {
				if (r[i] < 100 * currentState.ShapeDmin)
					continue;

				variancer += (r[i] - avgr) * (r[i] - avgr);
			}

			if (variancer < currentState.ShapeVariance) {
				for (auto it = finalpoints.begin(); it != finalpoints.end(); it++) {
					if ((points[k].x - it->x) * (points[k].x - it->x) + (points[k].y - it->y) * (points[k].y - it->y)
						< (long long)avgr * (long long)avgr / 10000) {
						isPoint = false;
						break;
					}
				}
				if (isPoint) {
					finalpoints.push_back(points[k]);
					circles.push_back(Vec3f(points[k].x, points[k].y, (float)avgr / 100));
				}
					
			}

		}
		break;

	case 2:
		if (!img.isContinuous())
			return;

		for (int i = 0; i < img.rows; i++) {
			uchar * data = img.ptr<uchar>(i);
			int start = 0, end = 0;
			for (int j = 1; j < img.cols; j++) {
				if (data[j - 1] < data[j]) {
					start = j;
				}
				else if (data[j - 1] > data[j]) {
					end = j;
					if (start > 0) {
						if (end - start < currentState.ShapeCorner)
							points.push_back(Point(start + (end - start) / 2, i));
					}
				}
			}
		}

		for (int i = 0; i < points.size(); i++) {
			if (points[i].y == 0) {
				
				continue;
			}
				
			uchar * data = img.ptr<uchar>(points[i].y - 1);
			bool isPoint = true;
			for (int j = -currentState.ShapeCorner / 2; j < currentState.ShapeCorner / 2; j++) {
				if (data[points[i].x + j] != 0) {
					isPoint = false;
					break;
				}
			}
			if (isPoint) {
				points2.push_back(points[i]);
			}
		}
		points = points2;


		break;
	}

	TSRResultLock.lock();
	TSRResult.circles = circles;
	TSRResult.points = finalpoints;
	TSRResult.progressPoints = points;
	TSRResultLock.unlock();
}

void TSR::BGR2HSI(const Mat& src, Mat& channelH, Mat& channelS, Mat& channelI) {
	Mat matBGR[3];
	Mat tmp = Mat(src.rows, src.cols, CV_32FC1);
	split(src, matBGR);
	Mat channelB, channelG, channelR;
	matBGR[0].convertTo(channelB, CV_32FC1);
	matBGR[1].convertTo(channelG, CV_32FC1);
	matBGR[2].convertTo(channelR, CV_32FC1);

	Mat matMin, matSum;
	add(channelB, channelG, matSum); // R G B 之和
	add(matSum, channelR, matSum);
	//divide(channelB, matSum, channelB);  // 求解 b g r
	//divide(channelG, matSum, channelG);
	//divide(channelR, matSum, channelR);

	// 计算强度 I
	channelI.create(src.rows, src.cols, CV_32FC1);
	divide(matSum, 3, channelI);

	// 计算饱和度 s
	channelS.create(src.rows, src.cols, CV_32FC1);
	min(channelB, channelG, matMin);
	min(matMin, channelR, matMin);
	divide(matMin, channelI, tmp);
	subtract(Mat(src.rows, src.cols, CV_32FC1, Scalar(1)), tmp, channelS);
	multiply(channelS, Mat(src.rows, src.cols, CV_32FC1, Scalar(100)), channelS);

	// 计算 h
	channelH.create(src.rows, src.cols, CV_32FC1);
	float* bData = channelB.ptr<float>(0);
	float* gData = channelG.ptr<float>(0);
	float* rData = channelR.ptr<float>(0);
	float* hData = channelH.ptr<float>(0);
	float r, g, b, temp;
	for (int i = 0; i < src.rows * src.cols; i++) {
		b = bData[i]; g = gData[i]; r = rData[i];

		// 单独处理 灰度图像
		if (b == g && b == r) {
			hData[i] = 0.0f;
			continue;
		}

		temp = 0.5 * ((r - g) + (r - b)) / sqrt((r - g)*(r - g) + (r - b)*(g - b));
		if (b <= g) {
			hData[i] = 57.2958 * acos(temp);
		}
		else {
			hData[i] = 360 - 57.2958 * acos(temp);
		}
	}

	// 仅用于调试，归一化后转成8UC1显示出来
	//multiply(channelH, Mat(src.rows, src.cols, CV_32FC1, Scalar(0.708)), channelH);
	//multiply(channelS, Mat(src.rows, src.cols, CV_32FC1, Scalar(255)), channelS);
	//channelH.convertTo(channelH, CV_8UC1);
	//channelS.convertTo(channelS, CV_8UC1);
	//channelI.convertTo(channelI, CV_8UC1);
}

void TSR::BGR2HSI_2(const Mat& src, Mat& channelH, Mat& channelS, Mat& channelI) {
	Mat matBGR[3];
	split(src, matBGR);
	Mat matMin, matMax;

	min(matBGR[0], matBGR[1], matMin);
	min(matMin, matBGR[2], matMin);
	max(matBGR[0], matBGR[1], matMax);
	max(matMin, matBGR[2], matMax);

	Mat tmp = Mat(src.rows, src.cols, CV_32FC1);
	
	Mat channelB, channelG, channelR;
	matBGR[0].convertTo(channelB, CV_32FC1);
	matBGR[1].convertTo(channelG, CV_32FC1);
	matBGR[2].convertTo(channelR, CV_32FC1);

	Mat matSum;
	add(channelB, channelG, matSum); // R G B 之和
	add(matSum, channelR, matSum);
	//divide(channelB, matSum, channelB);  // 求解 b g r
	//divide(channelG, matSum, channelG);
	//divide(channelR, matSum, channelR);

	// 计算强度 I
	channelI.create(src.rows, src.cols, CV_32FC1);
	divide(matSum, 3, channelI);

	// 计算饱和度 s
	channelS.create(src.rows, src.cols, CV_32FC1);
	
	divide(matMin, channelI, tmp);
	subtract(Mat(src.rows, src.cols, CV_32FC1, Scalar(1)), tmp, channelS);
	multiply(channelS, Mat(src.rows, src.cols, CV_32FC1, Scalar(100)), channelS);

	// 计算 h
	channelH.create(src.rows, src.cols, CV_32FC1);
	float* bData = channelB.ptr<float>(0);
	float* gData = channelG.ptr<float>(0);
	float* rData = channelR.ptr<float>(0);
	float* hData = channelH.ptr<float>(0);
	float r, g, b, temp;
	for (int i = 0; i < src.rows * src.cols; i++) {
		b = bData[i]; g = gData[i]; r = rData[i];

		// 单独处理 灰度图像
		if (b == g && b == r) {
			hData[i] = 0.0f;
			continue;
		}

		temp = 0.5 * ((r - g) + (r - b)) / sqrt((r - g)*(r - g) + (r - b)*(g - b));
		if (b <= g) {
			hData[i] = 57.2958 * acos(temp);
		}
		else {
			hData[i] = 360 - 57.2958 * acos(temp);
		}
	}

	// 仅用于调试，归一化后转成8UC1显示出来
	//multiply(channelH, Mat(src.rows, src.cols, CV_32FC1, Scalar(0.708)), channelH);
	//multiply(channelS, Mat(src.rows, src.cols, CV_32FC1, Scalar(255)), channelS);
	//channelH.convertTo(channelH, CV_8UC1);
	//channelS.convertTo(channelS, CV_8UC1);
	//channelI.convertTo(channelI, CV_8UC1);
}