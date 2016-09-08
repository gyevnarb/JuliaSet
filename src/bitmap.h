#pragma once

#include <iostream>
#include <complex>
#include <vector>

#include "pixel.h"

using complex = std::complex<double>;
using bitvector8 = std::vector<std::vector<uint_fast8_t>>;
using doublevector = std::vector<std::vector<double>>;
using pixelvector = std::vector<std::vector<pixel>>;

namespace bitmap
{
	void drawbmp(const bitvector8 & data, const char * filename, const uint_fast64_t & width, const uint_fast64_t & height);
	void drawbmp(const pixelvector & data, const char * filename, const uint_fast64_t & width, const uint_fast64_t & height);
}

