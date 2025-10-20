#pragma once

#include "global_data/SimParams.hpp"
#include <string>

const double PI = 3.14159265358979323846;

// Parse SimParams.ini
bool parseSimParams(const std::string& filename, SimParams& params);