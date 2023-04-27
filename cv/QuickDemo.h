#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/types_c.h"

class QuickDemo
{
public:
	void ColorSpaceDemo(cv::Mat& img);
	void CreateMatDemo();
	void PixelPtrDemo(cv::Mat& img);
	void OperatorDemo(cv::Mat& img);

	static void OnLightness(int lightness, void* userdata);
	static void OnContrast(int contrast, void* userdata);
	void TrackBarDemo(cv::Mat& img);

	void KeyEventDemo(cv::Mat& img);
	void ColorStyleDemo(cv::Mat& img);		
	void BitwiseDemo(cv::Mat& img);
	void SplitMergeDemo(cv::Mat& img);
	void InRangeDemo(cv::Mat& img);
	void PixelStatistic(cv::Mat& img);
	void DrawingDemo(cv::Mat& img);
	void RandomDemo();
	void PolylineDrawing();

	void MouseDrawingDemo(cv::Mat& img);
private:
	static cv::Mat temp;
	static cv::Point startPoint;
	static cv::Point stopPoint;
	static void OnMouseEvent(int event_, int x, int y, int flag, void* userdata);
};