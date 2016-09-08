#include "pixel.h"

pixel::pixel(colours colour)
{
	switch (colour)
	{
	case colours::RED:
		rgbRed = 1.0;
		break;
	case colours::GREEN:
		rgbGreen = 1.0;
		break;
	case colours::BLUE:
		rgbBlue = 1.0;
		break;
	case colours::WHITE:
		rgbRed = 1.0;
		rgbGreen = 1.0;
		rgbBlue = 1.0;
		break;
	case colours::BLACK:
		break;
	case colours::CYAN:
		rgbGreen = 1.0;
		rgbBlue = 1.0;
		break;
	case colours::MAGENTA:
		rgbRed = 1.0;
		rgbBlue = 1.0;
		break;
	case colours::YELLOW:
		rgbRed = 1.0;
		rgbGreen = 1.0;
		break;
	default:
		break;
	}
}
