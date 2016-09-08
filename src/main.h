#pragma once

#include "pixel.h"
#include "julia_set.h"
#include "bitmap.h"

constexpr double phi = 1.61803398875;
constexpr double pi = 3.141592654;

std::string complex_to_string(const complex & parameter);
void printResult(const std::string & fn, const julia_set & js, const std::string & dest, const bool & colour);
int handleInput(int argc, char * argv[]);
