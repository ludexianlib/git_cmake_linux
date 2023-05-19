#pragma once
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"

class Tutorial
{
public:
	void CommandLine(int argc, char* argv[]);
	void Sharpen(const cv::Mat& src, cv::Mat& dst);
	void PixelOperate(cv::Mat& src);
	void DiscreteFourierTransform(cv::Mat& src);
	void OperateFile();
};

class MyData
{
public:
	MyData();
	MyData(int a, std::string id);
	void write(cv::FileStorage& fs) const;
	void read(const cv::FileNode& node);
public:
	int A;
	std::string id;
};

// 读写类成员变量需要的静态函数
static void write(cv::FileStorage& fs, const std::string&, const MyData& x);
static void read(const cv::FileNode& node, MyData& m, const MyData& default_ = MyData());
static std::ostream& operator<<(std::ostream& out, const MyData& m);