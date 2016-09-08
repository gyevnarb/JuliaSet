#pragma once

#include <iostream>

enum class colours
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	BLACK,
	CYAN,
	MAGENTA,
	YELLOW
};

class pixel
{
public:
	pixel() = default;
	pixel(colours colour);
	pixel(const double & r, const double & g, const double & b) : rgbRed(r), rgbGreen(g), rgbBlue(b) { }

	inline pixel red(double a) const { return pixel(a, 0.0, 0.0); }
	inline pixel yellow(double a) const { return pixel(1.0, a, 0.0); }
	inline pixel green(double a) const { return pixel(1.0 - a, 1.0, 0.0); }
	inline pixel blue(double a) const { return pixel(0.0, 1.0 - a, a); }
	inline pixel white(double a) const { return pixel(a, a, 1.0); }

	inline double getRedComponent() const { return rgbRed; }
	inline double getGreenComponent() const { return rgbGreen; }
	inline double getBlueComponent() const { return rgbBlue; }

	inline uint_fast8_t getRedByte() const { return static_cast<uint_fast8_t>(std::round(255.0 * rgbRed)); }
	inline uint_fast8_t getGreenByte() const { return static_cast<uint_fast8_t>(std::round(255.0 * rgbGreen)); }
	inline uint_fast8_t getBlueByte() const { return static_cast<uint_fast8_t>(std::round(255.0 * rgbBlue)); }

private:
	double rgbRed = 0.0;
	double rgbGreen = 0.0;
	double rgbBlue = 0.0;

};
