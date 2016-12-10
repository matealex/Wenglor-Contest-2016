#include "Pixel.h"

string Pixel::toString()
{
	return "(" + to_string(R) + " " + to_string(G) + " " + to_string(B) + ")";
}

bool Pixel::operator==(Pixel b)
{
	return R == b.R && G == b.G && B == b.B;
}
