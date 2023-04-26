#include "opencv2/opencv.hpp"
#include "QuickDemo.h"

int main()
{
	cv::Mat img = cv::imread("./img/test.png");
	if (img.empty())
		return -1;
	
	QuickDemo demo;
	demo.InRangeDemo(img);

	cv::waitKey(0);

	return 0;
}