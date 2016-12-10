#pragma once
#include <opencv2/opencv.hpp>
#include <list>
#include <iostream>
#include <fstream>
#include "PixelOperation.h"

using namespace cv;

#define DLLEXPORT __declspec(dllexport)

namespace ImageOperations
{
	list<PixelOperation> operations;
	int degree;

	void readOperationFile(list<PixelOperation>& operations, int& degree);
	void optimizeOperations(list<PixelOperation>& operations, int& degree);
	void applyOperations(const int& imageNumber, const int& degree, const list<PixelOperation>& operations);
	void rotate(Mat& src, const int& angle);

	extern "C"
	{
		DLLEXPORT void readOperationFile();
		DLLEXPORT void processAllImages();
		DLLEXPORT void processImage(int imageNumber);
	}
}
