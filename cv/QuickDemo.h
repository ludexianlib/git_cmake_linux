#pragma once

#include "opencv2/opencv.hpp"

class QuickDemo
{
public:
	void ColorSpaceDemo(cv::Mat& img);
	void CreateMatDemo();
	void PixelPtrDemo(cv::Mat& img);
	void OperatorDemo(cv::Mat& img);

	static void OnLightness(int lightness, void* userdata);
	static void OnContrast(int lightness, void* userdata);
	void TrackBarDemo(cv::Mat& img);

	void KeyEventDemo(cv::Mat& img);
	void ColorStyleDemo(cv::Mat& img);		
	void BitwiseDemo(cv::Mat& img);
	void SplitMergeDemo(cv::Mat& img);
	void InRangeDemo(cv::Mat& img);
};