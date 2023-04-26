#include "QuickDemo.h"
#include <iostream>
#include <vector>

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
	cv::namedWindow("128_0_128.png", CV_WINDOW_NORMAL);
	cv::namedWindow("0_128_128.png", CV_WINDOW_NORMAL);

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
			cv::cvtColor(img, dst, CV_BGR2GRAY);
		}
		else if (key == 0x32)
		{
			std::cout << "key down: #2" << std::endl;
			cv::cvtColor(img, dst, CV_BGR2HSV);
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
	cv::cvtColor(img, hsv, CV_BGR2HSV);
	cv::Mat mask;
	// 相当于二值化, 查询目标图像是否在范围内
	cv::inRange(hsv, cv::Scalar(35, 43, 46), cv::Scalar(255, 200, 128), mask);
	cv::imshow("mask", mask);

	cv::Mat red = cv::Mat::zeros(img.size(), img.type());
	red = cv::Scalar(40, 40, 200);
	cv::bitwise_not(mask, mask);
	img.copyTo(red, mask);
	cv::imshow("roi", red);
}
