﻿#pragma once
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"

class Tutorial
{
public:
	void CommandLine(int argc, char* argv[]);
	void Sharpen(const cv::Mat& src, cv::Mat& dst);
	void PixelOperate(cv::Mat& src);
	void DiscreteFourierTransform(cv::Mat& src);
	void OperateFile();

	void ParallelizeComputing();
	int Mandelbrot(std::complex<float>& z0, const int max);
	int MandelbrotFormula(std::complex<float>& z0, const int max = 500);

	void ErosionDilation(cv::Mat& src);
	void HitAndMiss();
	void ExtraLine(cv::Mat& src);
	void Pyramid(cv::Mat& src);
	void Thresholding(cv::Mat& src);
	void HSVThreshold(cv::Mat& src);
	void MakeBorder(cv::Mat& src);
	void Soble(cv::Mat& src);
	void LaplacianOperator(cv::Mat& src);

	static void CannyThreshold(int low, void* data);
	void CannyTrackbar(cv::Mat& src);
	void HoughLinesTransform(cv::Mat& src); // lines / circles

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