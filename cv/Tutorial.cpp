#include "Tutorial.h"
#include <math.h>

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
		// 参考: https://docs.opencv.org/4.3.0/d3/dc1/tutorial_basic_linear_transform.html
		// 像素操作修改亮度和对比度
		cv::Mat alphaImg = cv::Mat::zeros(src.size(), CV_32FC3);
		cv::Mat grammaImg = cv::Mat::zeros(src.size(), CV_32FC3);
		float alpha = 1.3f;
		int beta = 40;
		float gramma = 0.4f;
		for (int i = 0; i < src.rows; i++)
		{
			uchar* srcPtr = src.ptr<uchar>(i);
			float* alphaPtr = alphaImg.ptr<float>(i);
			float* gramamPtr = grammaImg.ptr<float>(i);
			for (int j = 0; j < src.cols; j++)
			{
				for (int k = 0; k < src.channels(); k++)
				{
					// (alpha * I(i, j) + beta)
					*alphaPtr++ = alpha * (float)(*srcPtr) + beta; 
					// (I(i, j) / 255.0) ** gramma * 255.0;
					*gramamPtr++ = pow((float)(*srcPtr) / 255.0f, gramma) * 255.0f; 
					*srcPtr++;
				}
			}
		}
		alphaImg.convertTo(alphaImg, CV_8UC3);
		grammaImg.convertTo(grammaImg, CV_8UC3);
		cv::imshow("origin", src);
		cv::imshow("alphaImg", alphaImg);
		cv::imshow("grammaImg", grammaImg);
	}

}

void Tutorial::DiscreteFourierTransform(cv::Mat& src)
{
	// 计算变换最优尺寸
	int m = cv::getOptimalDFTSize(src.rows);
	int n = cv::getOptimalDFTSize(src.cols);

	cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
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

void Tutorial::OperateFile()
{
	const char* xmlName = "./img/test.xml";
	cv::Mat R = cv::Mat_<uchar>::eye(3, 3),
		T = cv::Mat_<float>::zeros(3, 1);
	MyData myData(99, "data99");

	{	// write
		cv::FileStorage fs(xmlName, cv::FileStorage::WRITE);
		fs << "int" << 100;

		fs << "images" << "[";
		fs << "test.png" << "../data/boom.jpg";
		fs << "]";

		fs << "mapping" << "{" << "One" << 1 << "}";
		fs << "R" << R;
		fs << "T" << T;
		fs << "MyData" << myData;
		fs.release();
	}

	{	// read
		cv::FileStorage fs;
		fs.open(xmlName, cv::FileStorage::READ);
		int int_ = (int)fs["int"];

		cv::FileNode node = fs["images"];
		if (node.type() != cv::FileNode::SEQ)
			exit(-1);
		cv::FileNodeIterator itBeg = node.begin(), itEnd = node.end();
		for (; itBeg != itEnd; ++itBeg)
			std::cout << (std::string)*itBeg << std::endl;

		node = fs["mapping"];
		std::cout << "One: " << (int)(node["One"]) << std::endl;

		MyData myData;
		cv::Mat R_, T_;
		fs["R"] >> R_;
		fs["T"] >> T_;
		fs["MyData"] >> myData;
		std::cout << "R = " << R_ << std::endl;
		std::cout << "T = " << T_ << std::endl;
		std::cout << "MyData = " << myData << std::endl;
		fs.release();
	}
}

void Tutorial::ParallelizeComputing()
{
	// 并行计算
	cv::Mat mandelbroImg(720, 1080, CV_8U);
	float x1 = -2.1f, x2 = 0.6f;
	float y1 = -1.2f, y2 = 1.2f;
	float scaleX = mandelbroImg.cols / (x2 - x1);
	float scaleY = mandelbroImg.rows / (y2 - y1);
	
#ifdef CV_CXX11
	cv::parallel_for_(cv::Range(0, mandelbroImg.rows * mandelbroImg.cols), [&](const cv::Range& range) {
		for (int r = range.start; r < range.end; r++)
		{
			int i = r / mandelbroImg.cols; // 第i行
			int j = r % mandelbroImg.cols; // 第j列

			float x0 = j / scaleX + x1;
			float y0 = i / scaleY + y1;
			
			std::complex<float> z0(x0, y0);
			uchar value = (uchar)MandelbrotFormula(z0);
			mandelbroImg.ptr<uchar>(i)[j] = value;
		}
	});
#else

#endif

	imshow("parallel.png", mandelbroImg);
}

int Tutorial::Mandelbrot(std::complex<float>& z0, const int max)
{
	std::complex<float> z = z0;
	for (int t = 0; t < max; t++)
	{
		if (z.real() * z.real() + z.imag() * z.imag() > 4.0f) return t;
		z = z * z + z0;
	}
	return max;
}

int Tutorial::MandelbrotFormula(std::complex<float>& z0, const int max)
{
	int value = Mandelbrot(z0, max);
	if (max - value == 0)
		return 0;
	return cvRound(sqrt(value / (float)max) * 255);
}

void Tutorial::ErosionDilation(cv::Mat & src)
{
	cv::Mat erodeDst, dilationDst;
	cv::Mat kernel = cv::Mat::ones(3, 3, CV_8U);
	
	// 像素取kernel计算结果最小值
	cv::erode(src, erodeDst, kernel);
	// 像素取kernel计算结果最大值
	cv::dilate(src, dilationDst, kernel);
	cv::imshow("src", src);
	cv::imshow("erodeDst", erodeDst);
	cv::imshow("dilationDst", dilationDst);

	// 降噪
	// Opening: 开操作-> dilate(erode(src))			morphologyEx(src, dst, 2, kernel)
	// Closing: 闭操作-> erode(dilate(src))			morphologyEx(src, dst, 3, kernel)
	
	// Gradient: 形态学梯度操作 dilate - erode		morphologyEx(src, dst, 4, kernel)

	// Top Hat: 礼帽: src - Opening					morphologyEx(src, dst, 5, kernel)
	// Black Hat: 黑帽: src - Closing				morphologyEx(src, dst, 6, kernel)
}

MyData::MyData()
	: A(0), id() 
{ }

MyData::MyData(int a, std::string id)
	: A(a), id(id) 
{}

void MyData::write(cv::FileStorage & fs) const
{
	// 写入类对象需要实现write
	fs << "{" << "A" << A << "id" << id << "}";
}

void MyData::read(const cv::FileNode& node)
{
	A = (int)node["A"];
	id = (std::string)node["id"];
}

void write(cv::FileStorage& fs, const std::string&, const MyData& x)
{
	x.write(fs);
}

void read(const cv::FileNode& node, MyData& m, const MyData& default_)
{
	if (node.empty())
		m = default_;
	else
		m.read(node);
}

std::ostream& operator<<(std::ostream& out, const MyData& m)
{
	out << "{ id = " << m.id << ", ";
	out << "A = " << m.A << "}";
	return out;
}
