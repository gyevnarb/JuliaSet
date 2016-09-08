#include "julia_set.h"

pixelvector julia_set::colour_julia_set()
{
	doublevector tmp_julia_set = setup_temp_julia_set();
	double mx = calcMax(tmp_julia_set);
	return colour_julia_set(tmp_julia_set, mx);
}

bitvector8 julia_set::bnw_julia_set()
{
	doublevector tmp_julia_set = setup_temp_julia_set();
	double mx = calcMax(tmp_julia_set);
	return bnw_julia_set(tmp_julia_set, mx);
}

complex julia_set::func(complex z)
{
	return z * z + parameter;
}

double julia_set::iterate(complex z)
{
	for (uint_fast64_t i = 0; i < iter_max; ++i)
	{
		z = func(z);
		if (std::abs(z) > threshold)
		{
			return static_cast<double>(i + 1) - log2(log2(std::abs(z)));
		}
	}
	return static_cast<double>(iter_max);
}

doublevector julia_set::setup_temp_julia_set()
{
	std::vector<double> tmp1(width);
	doublevector tmp_julia_set(height, tmp1);
	tmp_julia_set.reserve(height);

	double h_step = 2.0 * std::abs(imag_iv_min) / height, w_step = 2.0 * std::abs(real_iv_min) / width;

	for (uint_fast64_t i = 0; i != height; ++i)
#pragma omp parallel for simd
		for (uint_fast64_t j = 0; j != width; ++j)
			tmp_julia_set[i][j] = iterate(complex(real_iv_min + w_step * j, imag_iv_min + h_step * i));

	return tmp_julia_set;
}


bitvector8 julia_set::bnw_julia_set(const doublevector & data, const double & max)
{
	std::vector<uint_fast8_t> tmp(data[0].size());
	bitvector8 julia_set(data.size(), tmp);

	for (uint_fast64_t i = 0; i != data.size(); ++i)
		for (uint_fast64_t j = 0; j != data[0].size(); ++j)
			julia_set[i][j] = static_cast<uint_fast8_t>(std::round(255.0 * data[i][j] / max));

	return julia_set;
}

pixelvector julia_set::colour_julia_set(const doublevector & data, const double & max)
{
	std::vector<pixel> tmp(data[0].size());
	pixelvector tmp_coloured_julia_set(data.size(), tmp);

	for (uint_fast64_t i = 0; i != data.size(); ++i)
		for (uint_fast64_t j = 0; j != data[0].size(); ++j)
			tmp_coloured_julia_set[i][j] = colour(data[i][j] / max);

	return tmp_coloured_julia_set;
}

pixel julia_set::colour(const double & a)
{
	if (a <= 0.0)
		return pixel(colours::BLACK);
	else if (a <= 0.03)
		return pixel().red(a / 0.03);
	else if (a <= 0.1)
		return pixel().yellow((a - 0.03) / 0.07);
	else if (a <= 0.2)
		return pixel().green((a - 0.1) / 0.1);
	else if (a <= 0.4)
		return pixel().blue((a - 0.2) / 0.2);
	else if (a <= 1.0)
		return pixel().white((a - 0.4) / 0.6);
	else
		return pixel(colours::WHITE);
}

double julia_set::calcMax(const doublevector & data)
{
	double max = 1.0;
	for (uint_fast64_t i = 0; i != data.size(); ++i)
		max = std::max(max, *std::max_element(data[i].cbegin(), data[i].cend()));
	return max;
}
