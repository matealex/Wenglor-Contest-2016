#include "PixelOperation.h"

using namespace std;

string PixelOperation::toString()
{
	return "(" + original.toString() + "," + transformed.toString() + ")";
}

bool PixelOperation::hasSameOriginalPixelWith(PixelOperation otherOperation)
{
	return original == otherOperation.original;
}

bool PixelOperation::isInverseOperationWith(PixelOperation otherOperation)
{
	return original == otherOperation.transformed && transformed == otherOperation.original;
}

void PixelOperation::combineWith(PixelOperation otherOperation)
{
	if (transformed == otherOperation.original)
	{
		transformed = otherOperation.transformed;
	}
}
