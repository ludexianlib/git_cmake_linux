#include "Tutorial.h"

void Tutorial::CommandLine(int argc, char* argv[])
{
	const char* fileName = argc >= 2 ? argv[1] : "./img/test.png";

	cv::Mat src, dst0, dst1;
	if (argc >= 3 && !strcmp("G", argv[2]))
		src = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
	else
		src = cv::imread(fileName, cv::IMREAD_COLOR);

	if (src.empty())
		return;

	cv::namedWindow("input");
	cv::namedWindow("output");
	cv::imshow("input", src);

	double t = (double)cvGetTickCount();

	// 自定义卷积操作
	Sharpen(src, dst0);
	t = ((double)cvGetTickCount() - t) / cvGetTickFrequency();
	std::cout << "处理图片经过时间(s): " << t << std::endl;

	cv::imshow("output", dst0);
	cv::waitKey(0);

	// int arr[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
	// cv::Mat kernel = cv::Mat1i(3, 3, arr);
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

	t = (double)cvGetTickCount();

	// OpenCV自带卷积操作
	cv::filter2D(src, dst1, src.depth(), kernel);

	t = ((double)cvGetTickCount() - t) / cvGetTickFrequency();
	std::cout << "处理图片经过时间(s): " << t << std::endl;
	cv::imshow("output", dst1);
	cv::waitKey(0);
}

void Tutorial::Sharpen(const cv::Mat& src, cv::Mat& dst)
{
	CV_Assert(src.depth() == CV_8U);
	std::cout << "src depth: " << src.depth() << std::endl;
	std::cout << "src type: " << src.type() << std::endl;

	const int nChannels = src.channels();
	dst.create(src.size(), src.type());

	for (int j = 1; j < src.rows - 1; j++)
	{
		// 行指针
		const uchar* previous = src.ptr<uchar>(j - 1);
		const uchar* current = src.ptr<uchar>(j);
		const uchar* next = src.ptr<uchar>(j + 1);

		uchar* output = dst.ptr<uchar>(j);

		// 卷积计算过程
		for (int i = nChannels; i < nChannels * (src.cols - 1); i++)
		{
			output[i] = cv::saturate_cast<uchar>(5 * current[i] -
				current[i - nChannels] - current[i + nChannels] -
				previous[i] - next[i]);
		}
	}
	dst.row(0).setTo(cv::Scalar(0));
	dst.row(dst.rows - 1).setTo(cv::Scalar(0));
	dst.col(0).setTo(cv::Scalar(0));
	dst.col(dst.cols - 1).setTo(cv::Scalar(0));
}

void Tutorial::PixelOperate(cv::Mat& src)
{
	if (src.channels() == 1)
	{
		cv::Scalar intensity = src.at<uchar>(0, 0);
		std::cout << "scalar: " << intensity << std::endl;
		cv::imshow("origin", src);
		src.at<uchar>(0, 0) = 255;
		intensity = src.at<uchar>(0, 0);
		std::cout << "scalar: " << intensity << std::endl;
		cv::imshow("changed", src);
	}
	else if (src.channels() == 3)
	{
		cv::Vec3b vPixel = src.at<cv::Vec3b>(0, 1);
		std::cout << "vec uchar 3 channels: " << vPixel << std::endl;
		uchar b = vPixel.val[0];
		uchar g = vPixel.val[1];
		uchar r = vPixel.val[2];


	}

}
