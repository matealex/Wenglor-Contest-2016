#pragma once
#include <string>

using namespace std;

struct Pixel
{
	int R, G, B;

	string toString();
	bool operator==(Pixel b);
};
