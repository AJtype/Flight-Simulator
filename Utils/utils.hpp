#pragma once

#include "../global_data/SimParams.hpp"
#include <string>
#include <fstream>
#include <iostream>

const double PI = 3.14159265358979323846;

void trim(std::string& s);

// Parse SimParams.ini
bool parseSimParams(const std::string& filename, SimParams& params);
