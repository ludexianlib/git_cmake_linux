#include "QuickDemo.h"
#include <iostream>
#include <vector>
#include <unordered_map>

void QuickDemo::ColorSpaceDemo(cv::Mat& img)
{
	// 色彩空间转换
	cv::Mat hsv, gray;
	cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	cv::imshow("hsv.png", hsv);
	cv::imshow("gray.png", gray);
}

void QuickDemo::CreateMatDemo()
{

	// 设置窗口属性
#if (CV_VERSION_MAJOR == 4)
	cv::namedWindow("128_0_128.png", cv::WINDOW_NORMAL);
	cv::namedWindow("0_128_128.png", cv::WINDOW_NORMAL);
#else (CV_VERSION_MAJOR == 3)
	cv::namedWindow("128_0_128.png", CV_WINDOW_NORMAL);
	cv::namedWindow("0_128_128.png", CV_WINDOW_NORMAL);
#endif // CV_VERSION_MAJOR

	cv::Mat src = cv::Mat::ones(cv::Size(128, 128), CV_8UC3);
	src = cv::Scalar(128, 0, 128);
	cv::Mat copy;
	src.copyTo(copy);
	copy = cv::Scalar(0, 128, 128);
	cv::imshow("128_0_128.png", src);
	cv::imshow("0_128_128.png", copy);
}

void QuickDemo::PixelPtrDemo(cv::Mat& img)
{
	// 遍历图像像素点
	int rows = img.rows;
	int cols = img.cols;
	int dims = img.channels();
	std::cout << rows << " " << cols << " " << dims;

	for (int i = 0; i < rows; i++)
	{
		uchar* rowPtr = img.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			// 单通道
			if (dims == 1)
			{
				int pv = *rowPtr;
				*rowPtr = 255 - pv;
				rowPtr++;
			}
			// 三通道
			else if (dims == 3)
			{
				// [b, g, r]
				cv::Vec3b& bgr = img.at<cv::Vec3b>(i, j);

				*rowPtr++ = 255 - *rowPtr;	// b
				*rowPtr++ = 255 - *rowPtr;	// g
				*rowPtr++ = 255 - *rowPtr;	// r
			}
		}
	}
	cv::imshow("changed_pixel.png", img);
}

void QuickDemo::OperatorDemo(cv::Mat& img)
{
	cv::Mat src = cv::Mat::zeros(img.size(), img.type());
	cv::Mat dst = cv::Mat::zeros(img.size(), img.type());
	src = cv::Scalar(128, 55, 78);
	
	//cv::add(img, src, dst);
	cv::divide(src, img, dst);
	cv::imshow("divide_dst.png", dst);
}

void QuickDemo::OnLightness(int lightness, void* userdata)
{
	// 亮度
	cv::Mat img = *((cv::Mat*)userdata);
	cv::Mat src = cv::Mat::zeros(img.size(), img.type());
	cv::Mat dst = cv::Mat::zeros(img.size(), img.type());

	// dst = img * 1.0 + src * 0.0 + gamma
	cv::addWeighted(img, 1.0, src, 0.0, lightness, dst);
	cv::imshow("lightness_contrast.png", dst);
}

void QuickDemo::OnContrast(int contrast, void* userdata)
{
	// 对比度
	cv::Mat img = *((cv::Mat*)userdata);
	cv::Mat src = cv::Mat::zeros(img.size(), img.type());
	cv::Mat dst = cv::Mat::zeros(img.size(), img.type());
	double contrast_ = contrast / 100.0;
	cv::addWeighted(img, contrast_, src, 0.0, 0.0, dst);
	cv::imshow("lightness_contrast.png", dst);
}

void QuickDemo::TrackBarDemo(cv::Mat& img)
{
	cv::namedWindow("lightness_contrast.png");
	int lightness = 50;
	int max = 100;
	int contrast = 100;
	cv::createTrackbar("lbar", "lightness_contrast.png", &lightness, max, &QuickDemo::OnLightness, &img);
	cv::createTrackbar("cbar", "lightness_contrast.png", &contrast, 200, &QuickDemo::OnContrast, &img);
	OnLightness(lightness, &img);
	OnContrast(contrast, &img);
}

void QuickDemo::KeyEventDemo(cv::Mat& img)
{
	cv::Mat dst = cv::Mat::zeros(img.size(), img.type());
	while (true)
	{
		int key = cv::waitKey(100);
		if (key == 0x1B) // ESC
		{
			std::cout << "key down: #ESC" << std::endl;
			break;
		}
		else if (key == 0x31)
		{
			std::cout << "key down: #1" << std::endl;
#if (CV_VERSION_MAJOR == 4)
			cv::cvtColor(img, dst, cv::COLOR_BGR2GRAY);
#else (CV_VERSION_MAJOR == 3)
			cv::cvtColor(img, dst, CV_BGR2GRAY);
#endif // CV_VERSION_MAJOR
		}
		else if (key == 0x32)
		{
			std::cout << "key down: #2" << std::endl;
#if (CV_VERSION_MAJOR == 4)
			cv::cvtColor(img, dst, cv::COLOR_BGR2HSV);
#else (CV_VERSION_MAJOR == 3)
			cv::cvtColor(img, dst, CV_BGR2HSV);
#endif // CV_VERSION_MAJOR
		}
		else if (key == 0x33)
		{
			std::cout << "key down: #3" << std::endl;
			dst = cv::Scalar(128, 156, 98);
		}
		cv::imshow("key event", dst);
	}
}

void QuickDemo::ColorStyleDemo(cv::Mat& img)
{
	// 滤镜
	cv::Mat dst;
	int index = 0;
	while (true)
	{
		int key = cv::waitKey(500);
		if (key == 0x1B)
			break;
		cv::applyColorMap(img, dst, (index % 21));
		index++;
		cv::imshow("style.png", dst);
	}
}

void QuickDemo::BitwiseDemo(cv::Mat& img)
{
	// 位操作
	cv::Mat img1 = cv::Mat::zeros(img.size(), img.type());
	cv::Mat img2 = cv::Mat::zeros(img.size(), img.type());

	// -1为rectangle填充
	cv::rectangle(img1, cv::Rect(100, 100, 80, 80), cv::Scalar(75, 128, 175), -1, cv::LINE_8);
	cv::rectangle(img2, cv::Rect(150, 150, 80, 80), cv::Scalar(55, 128, 155), -1, cv::LINE_8);
	
	cv::Mat dst;
	//cv::bitwise_and(img1, img2, dst);	// 交集
	cv::bitwise_or(img1, img2, dst);	// 并集
	cv::imshow("bit_and.png", dst);
}

void QuickDemo::SplitMergeDemo(cv::Mat& img)
{
	// 通道分离
	std::vector<cv::Mat> vMat;
	cv::split(img, vMat);

	// 通道合并
	cv::Mat dst;
	vMat[0] = 0;
	cv::merge(vMat, dst);

	// 通道混合
		// 通道复制: 0-> 2, 1-> 1, 2->0 相当于BGR2RGB
	int from[] = { 0, 2, 1, 1, 2, 0 };
	cv::mixChannels(&img, 1, &dst, 1, from, 3);
	cv::imshow("mix", dst);
}

void QuickDemo::InRangeDemo(cv::Mat& img)
{
	// 颜色提取
	cv::Mat hsv;
#if (CV_VERSION_MAJOR == 4)
	cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
#else (CV_VERSION_MAJOR == 3)
	cv::cvtColor(img, hsv, CV_BGR2HSV);
#endif // CV_VERSION_MAJOR

	cv::Mat mask;
	// 相当于二值化, 查询目标图像是否在范围内
	cv::inRange(hsv, cv::Scalar(63, 0, 4), cv::Scalar(255, 35, 190), mask);
	cv::imshow("mask", mask);

	cv::Mat red = cv::Mat::zeros(img.size(), img.type());
	red = cv::Scalar(40, 40, 200);
	cv::bitwise_not(mask, mask);
	img.copyTo(red, mask);
	cv::imshow("roi", red);
}

void QuickDemo::PixelStatistic(cv::Mat& img)
{
	// 像素统计
	double minVal, maxVal;
	cv::Point minCol, maxCol;

	std::vector<cv::Mat> vMat;
	cv::split(img, vMat);
	std::unordered_map<int, char> uChannel = { {0, 'b'}, {1, 'g'}, {2, 'r'} };
	for (int i = 0; i < img.channels(); i++)
	{
		cv::minMaxLoc(vMat[i], &minVal, &maxVal, &minCol, &maxCol, cv::Mat());
		printf("%c-> min value: %.4f, max value: %.4f\n", uChannel[i], minVal, maxVal);
	}

	cv::Mat mean, stddev;
	cv::meanStdDev(img, mean, stddev);
	std::cout << "mean: " << mean << std::endl;
	std::cout << "stddev: " << stddev << std::endl;
}

void QuickDemo::DrawingDemo(cv::Mat& img)
{
	// 多边形绘制
#if (CV_VERSION_MAJOR == 4)
	cv::namedWindow("drawing.png", cv::WINDOW_NORMAL);
#else (CV_VERSION_MAJOR == 3)
	cv::namedWindow("drawing.png", CV_WINDOW_NORMAL);
#endif // CV_VERSION_MAJOR

	cv::Mat bg = cv::Mat::zeros(img.size(), img.type());
	cv::rectangle(img, cv::Rect(50, 50, 100, 100), cv::Scalar(24, 128, 155), 1, cv::LINE_8);
	cv::circle(img, cv::Point(100, 100), 50, cv::Scalar(155, 128, 24), -1, cv::LINE_AA);
	cv::line(img, cv::Point(50, 50), cv::Point(150, 150), cv::Scalar(128, 155, 24), 1, cv::LINE_4);

	cv::Mat dst;
	cv::ellipse(img, cv::RotatedRect(cv::Point(100, 100), cv::Size2f(100, 50), 0.0), cv::Scalar(128, 128, 0));
	cv::addWeighted(img, 0.7, bg, 0.3, 0, dst);
	cv::imshow("drawing.png", dst);
}

void QuickDemo::RandomDemo()
{
	// 随机生成坐标
	cv::Mat bg = cv::Mat::zeros(cv::Size(256, 256), CV_8UC3);
	int height = bg.rows;
	int width = bg.cols;
	cv::RNG rng(12345);
	while (true)
	{
		int key = cv::waitKey(100);
		if (key == 0x1B)
			break;
		int xPoint1 = rng.uniform(0, width);
		int yPoint1 = rng.uniform(0, height);
		int xPoint2 = rng.uniform(0, width);
		int yPoint2 = rng.uniform(0, height);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		bg = cv::Scalar(0, 0, 0);
		cv::line(bg, cv::Point(xPoint1, yPoint1), cv::Point(xPoint2, yPoint2), cv::Scalar(b, g, r), 1, cv::LINE_AA);
		cv::imshow("random.png", bg);
	}
}

void QuickDemo::PolylineDrawing()
{
	// 多边形绘制
	cv::Mat bg = cv::Mat::zeros(cv::Size(256, 256), CV_8UC3);
	std::vector<cv::Point> vPoint1 = {
		cv::Point(50, 50),
		cv::Point(100, 50),
		cv::Point(150, 150),
		cv::Point(75, 200),
		cv::Point(0, 150)
	};
	std::vector<cv::Point> vPoint2 = {
		cv::Point(100, 100),
		cv::Point(200, 100),
		cv::Point(150, 150)
	};
	cv::RNG rng(12345);
	cv::Scalar s1 = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	cv::Scalar s2 = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	//cv::fillPoly(bg, vPoint1, s1, cv::LINE_AA);
	//cv::polylines(bg, vPoint1, true, s2, 2, cv::LINE_AA);
	std::vector<std::vector<cv::Point>> vvPoints = { vPoint1, vPoint2 };
	cv::drawContours(bg, vvPoints, -1, s1);
	cv::imshow("polyline.png", bg);
}

// 定义鼠标事件静态变量
cv::Mat QuickDemo::temp;
cv::Point QuickDemo::startPoint(-1, -1);
cv::Point QuickDemo::stopPoint(-1, -1);

void QuickDemo::OnMouseEvent(int event_, int x, int y, int flag, void* userdata)
{
	// 鼠标响应事件回调函数
	cv::Mat img = *((cv::Mat*)userdata);
	if (event_ == cv::EVENT_LBUTTONDOWN)
	{
		// 开始绘制
		startPoint.x = x;
		startPoint.y = y;
		printf("start point: (%d, %d)\n", x, y);
	}
	else if (event_ == cv::EVENT_LBUTTONUP)
	{
		// 停止绘制
		stopPoint.x = x;
		stopPoint.y = y;
		int dx = stopPoint.x - startPoint.x;
		int dy = stopPoint.y - startPoint.y;
		if (dx >= 0 && dy > 0)
		{
			cv::Rect box(startPoint.x, startPoint.y, dx, dy);
			temp.copyTo(img);
			cv::imshow("roi.png", img(box));	
			cv::rectangle(img, box, cv::Scalar(128, 155, 24), 1, cv::LINE_AA);
			cv::imshow("mouse_event", img);
			startPoint.x = -1;
			startPoint.y = -1;
		}
	}
	else if (event_ == cv::EVENT_MOUSEMOVE)
	{
		// 绘制中
		if (startPoint.x > 0 && startPoint.y > 0)
		{
			stopPoint.x = x;
			stopPoint.y = y;
			int dx = stopPoint.x - startPoint.x;
			int dy = stopPoint.y - startPoint.y;
			if (dx >= 0 && dy > 0)
			{
				cv::Rect box(startPoint.x, startPoint.y, dx, dy);
				temp.copyTo(img);
				cv::rectangle(img, box, cv::Scalar(128, 155, 24), 1, cv::LINE_AA);
				cv::imshow("mouse_event", img);
			}
		}
	}
}

void QuickDemo::MouseDrawingDemo(cv::Mat& img)
{
	// 鼠标事件
	cv::namedWindow("mouse_event");
	cv::setMouseCallback("mouse_event", OnMouseEvent, &img);
	cv::imshow("mouse_event", img);
	temp = img.clone();
}

void QuickDemo::NormalizeDemo(cv::Mat& img)
{
	// 数据归一化
	cv::Mat dst;
	img.convertTo(img, CV_32F);
	printf("convert 32f img channel: %d\n", img.channels());
	std::cout << "pixel value: " << img.at<cv::Vec3f>(0, 1) << std::endl;
	printf("pixel value: %f\n", img.at<float>(0, 3));
	printf("pixel value: %f\n", img.at<float>(0, 4));
	printf("pixel value: %f\n", img.at<float>(0, 5));
	cv::normalize(img, dst, 1.0, 0.0, cv::NORM_MINMAX);
	cv::imshow("normalize", dst);
}

void QuickDemo::ResizeDemo(cv::Mat& img)
{
	// 缩放图像
	cv::Mat zoomIn, zoomOut;
	int rows = img.rows;
	int cols = img.cols;
	std::cout << (double)rows / 1.5 << std::endl;
	std::cout << rows / 1.5 << std::endl;
	cv::resize(img, zoomIn, cv::Size2d(rows / 1.5, cols / 1.5), 0, 0, cv::INTER_LINEAR);
	cv::resize(img, zoomOut, cv::Size2d(rows * 1.2, cols * 1.2), 0, 0, cv::INTER_LINEAR);
	cv::imshow("zoom in", zoomIn);
	cv::imshow("zoom out", zoomOut);
}
