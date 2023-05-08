#pragma once
#include <iostream>
#include "opencv2/opencv.hpp"

class Tutorial
{
public:
	void CommandLine(int argc, char* argv[]);
	void Sharpen(const cv::Mat& src, cv::Mat& dst);
	void PixelOperate(cv::Mat& src);
};