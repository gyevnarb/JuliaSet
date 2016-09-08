#pragma once

#include <iostream>
#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
#include <string>

#include "pixel.h"

using complex = std::complex<double>;
using bitvector8 = std::vector<std::vector<uint_fast8_t>>;
using doublevector = std::vector<std::vector<double>>;
using pixelvector = std::vector<std::vector<pixel>>;

class julia_set
{
public:
	julia_set() = default;
	julia_set(const complex & param) 
		: parameter(param) {}
	julia_set(const complex & param, const uint_fast64_t & w, const uint_fast64_t & h) 
		: parameter(param), width(w), height(h) {}
	julia_set(const complex & param, const double & thres, const uint_fast64_t & w, const uint_fast64_t & h) 
		: parameter(param), threshold(thres), width(w), height(h) {}
	julia_set(const complex & param, const double & thres, const uint_fast64_t & it_mx, const uint_fast64_t & w, const uint_fast64_t & h) 
		: parameter(param), threshold(thres), iter_max(it_mx), width(w), height(h) {}
	julia_set(const complex & param, const double & thres, const uint_fast64_t & it_mx, const uint_fast64_t & w, const uint_fast64_t & h, const double & riv, const double & iiv) 
		: parameter(param), threshold(thres), iter_max(it_mx), width(w), height(h), real_iv_min(riv), imag_iv_min(iiv) {}
	julia_set(const complex & param, const double & thres) 
		: parameter(param), threshold(thres) {}
	julia_set(const complex & param, const uint_fast64_t & it_mx)
		: parameter(param), iter_max(it_mx) {}
	julia_set(const complex & param, const double & thres, const uint_fast64_t & it_mx) 
		: parameter(param), threshold(thres), iter_max(it_mx) {}

	pixelvector colour_julia_set();
	bitvector8 bnw_julia_set();

	uint_fast64_t getWidth() const { return width; }
	void setWidth(const uint_fast64_t & w) { width = w; }
	uint_fast64_t getHeight() const { return height; }
	void setHeight(const uint_fast64_t & h) { height = h; }
	complex getParameter() const { return parameter; }
	void setParameter(const complex & z) { parameter = z; }
	double getThreshold() const { return threshold; }
	void setThreshold(const double & t) { threshold = t; }
	uint_fast64_t getIterMax() const { return iter_max; }
	void setIterMax(const uint_fast64_t & im) { im < 512 ? iter_max = 512 : iter_max = im; }
	std::vector<double> getJSItnterval() const { return std::vector<double> {real_iv_min, imag_iv_min}; }
	void setRealIvMin(const double & riv) { real_iv_min = riv; }
	void setImagIvMin(const double & iiv) { imag_iv_min = iiv; }

private:
	uint_fast64_t iter_max = 1024Ui64;
	uint_fast64_t width = 1920Ui64;
	uint_fast64_t height = 1080Ui64;
	complex parameter = complex(0.0, 0.0);
	double threshold = 2.0;
	double real_iv_min = -1.5, imag_iv_min = -1.5;

	complex func(complex z);
	double iterate(complex z);
	doublevector setup_temp_julia_set();
	bitvector8 bnw_julia_set(const doublevector & data, const double & max);
	pixelvector colour_julia_set(const doublevector & data, const double & max);
	pixel colour(const double & a);
	double calcMax(const doublevector & data);

};

