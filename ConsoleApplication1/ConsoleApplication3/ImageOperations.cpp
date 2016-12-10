#include "ImageOperations.h"

void ImageOperations::applyOperations(const int& imageNumber, const int& degree, const list<PixelOperation>& operations)
{
	auto sourceImagePath = ".\\Input Files\\Input-" + to_string(imageNumber) + ".bmp";
	auto destinationImagePath = ".\\Output Files\\Output-" + to_string(imageNumber) + ".bmp";

	Mat sourceImage = imread(sourceImagePath, IMREAD_COLOR);

	if (sourceImage.empty())
	{
		cout << "Could not open or find the image " << imageNumber << '\n';
		return;
	}

	rotate(sourceImage, degree);

	for (auto i = operations.begin(); i != operations.end(); ++i)
	{
		Mat mask;
		auto originalPixel = Scalar(i->original.B, i->original.G, i->original.R);
		auto transformedPixel = Scalar(i->transformed.B, i->transformed.G, i->transformed.R);

		inRange(sourceImage, originalPixel, originalPixel, mask);
		sourceImage.setTo(transformedPixel, mask);
	}

	imwrite(destinationImagePath, sourceImage);
}

void ImageOperations::rotate(Mat& src, const int& angle)
{
	if (angle == 270 || angle == -90)
	{
		transpose(src, src);
		flip(src, src, 0);
	}
	else if (angle == 180 || angle == -180)
	{
		flip(src, src, -1);
	}
	else if (angle == 90 || angle == -270)
	{
		transpose(src, src);
		flip(src, src, 1);
	}
}

void ImageOperations::readOperationFile(list<PixelOperation>& operations, int& degree)
{
	ifstream operationsFile(".\\Operations.txt");
	degree = 0;

	if (operationsFile.is_open())
	{
		string buffer;
		while (getline(operationsFile, buffer))
		{
			if (buffer.find("rotate") != string::npos)
			{
				buffer = buffer.substr(7);
				degree += stoi(buffer);
			}
			else
			{
				buffer = buffer.substr(5);

				Pixel first, second;
				istringstream ss(buffer);

				string token;
				getline(ss, token, ' ');
				first.R = stoi(token);
				getline(ss, token, ' ');
				first.G = stoi(token);
				getline(ss, token, ' ');
				first.B = stoi(token);

				getline(ss, token, ' ');
				second.R = stoi(token);
				getline(ss, token, ' ');
				second.G = stoi(token);
				getline(ss, token, ' ');
				second.B = stoi(token);

				if (first == second)
				{
					continue;
				}

				PixelOperation operation;
				operation.original = first;
				operation.transformed = second;
				operations.push_back(operation);
			}
		}
		operationsFile.close();
	}
	else
	{
		cout << "Unable to open Operation file" << endl;
	}

	optimizeOperations(operations, degree);
}

void ImageOperations::optimizeOperations(list<PixelOperation>& operations, int& degree)
{
	degree = degree % 360;
	for (auto i = operations.begin(); i != prev(operations.end()); ++i)
	{
		if ((*i).isInvalid)
		{
			continue;
		}

		for (auto j = next(i); j != operations.end(); ++j)
		{
			if ((*i).isInverseOperationWith(*j))
			{
				(*i).isInvalid = true;
				break;
			}

			if ((*i).hasSameOriginalPixelWith(*j))
			{
				(*j).isInvalid = true;
				continue;;
			}

			(*i).combineWith(*j);
		}
	}

	operations.remove_if([](PixelOperation op)
		{
			return op.isInvalid;
		});
}

void ImageOperations::readOperationFile()
{
	readOperationFile(operations, degree);
}

void ImageOperations::processAllImages()
{
	for (auto i = 1; i <= 10; i++)
	{
		applyOperations(i, degree, operations);
	}
}

void ImageOperations::processImage(int imageNumber)
{
	applyOperations(imageNumber, degree, operations);
}
