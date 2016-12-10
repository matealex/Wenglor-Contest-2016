#pragma once
#include "Pixel.h"

struct PixelOperation
{
	Pixel original;
	Pixel transformed;
	bool isInvalid = false;

	string toString();
	bool hasSameOriginalPixelWith(PixelOperation otherOperation);
	bool isInverseOperationWith(PixelOperation otherOperation);
	void combineWith(PixelOperation otherOperation);
};
