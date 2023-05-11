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

	// 设置窗口属性
	double t;
#if (CV_VERSION_MAJOR == 4)
	t = (double)cv::getTickCount();
	// 自定义卷积操作
	Sharpen(src, dst0);
	t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
#else (CV_VERSION_MAJOR == 3)
	t = (double)cvGetTickCount();
	Sharpen(src, dst0);
	t = ((double)cvGetTickCount() - t) / cvGetTickFrequency();
#endif // CV_VERSION_MAJOR

	std::cout << "处理图片经过时间(s): " << t << std::endl;
	cv::imshow("output", dst0);
	cv::waitKey(0);

	// int arr[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
	// cv::Mat kernel = cv::Mat1i(3, 3, arr);
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
#if (CV_VERSION_MAJOR == 4)
	t = (double)cv::getTickCount();
#else (CV_VERSION_MAJOR == 3)
	t = (double)cvGetTickCount();
#endif // CV_VERSION_MAJOR

	// OpenCV自带卷积操作
	cv::filter2D(src, dst1, src.depth(), kernel);

#if (CV_VERSION_MAJOR == 4)
	t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
#else (CV_VERSION_MAJOR == 3)
	t = ((double)cvGetTickCount() - t) / cvGetTickFrequency();
#endif // CV_VERSION_MAJOR
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

void Tutorial::DiscreteFourierTransform(cv::Mat& src)
{
	// 计算变换最优尺寸
	int m = cv::getOptimalDFTSize(src.rows);
	int n = cv::getOptimalDFTSize(src.cols);

#if (CV_VERSION_MAJOR == 4)
	cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
#else (CV_VERSION_MAJOR == 3)
	cv::cvtColor(src, src, COLOR_BGR2GRAY);
#endif // CV_VERSION_MAJOR

	// 多出部分用0填充
	cv::Mat padded;
	cv::copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };

	cv::Mat complexDst;
	cv::merge(planes, 2, complexDst); // 通道合并

	cv::dft(complexDst, complexDst);

	cv::split(complexDst, planes);
	// 计算DFT幅值
	cv::magnitude(planes[0], planes[1], planes[0]); // M = sqrt(Re(DFT(I)) ^ 2 + Im(DFT(I) ^ 2)
	cv::Mat magSrc = planes[0];

	// 切换到对数标度 M_log = log(1 + M)
	magSrc += cv::Scalar::all(1);
	cv::log(magSrc, magSrc);

	magSrc = magSrc(cv::Rect(0, 0, magSrc.cols & -2, magSrc.rows & -2)); // 如果行或列为奇数则裁剪

	// 将四个角转换到中心
	int cx = magSrc.cols / 2;
	int cy = magSrc.rows / 2;
	cv::Mat roi0(magSrc, cv::Rect(0, 0, cx, cy));
	cv::Mat roi1(magSrc, cv::Rect(cx, 0, cx, cy));
	cv::Mat roi2(magSrc, cv::Rect(0, cy, cx, cy));
	cv::Mat roi3(magSrc, cv::Rect(cx, cy, cx, cy));
	cv::Mat tmp;
	roi0.copyTo(tmp);
	roi3.copyTo(roi0);
	tmp.copyTo(roi3);

	roi1.copyTo(tmp);
	roi2.copyTo(roi1);
	tmp.copyTo(roi2);

	// 归一化后方便显示
	cv::normalize(magSrc, magSrc, 0, 1, cv::NORM_MINMAX);
	cv::imshow("magnitude", magSrc);
}
