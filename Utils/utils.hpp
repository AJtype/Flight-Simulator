#pragma once

#include "../global_data/SimParams.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

const double PI = 3.14159265358979323846;

void trim(std::string& s);

// Parse SimParams.ini
bool parseSimParams(const std::string& filename, SimParams& params);

// Parse SimCmds.txt
bool parseCommands(const std::string& filename, std::vector<Command>& commands);

// Convert degrees to radians
double degToRad(const double deg);

// Convert radians to degrees
double radToDeg(const double rad);

// Normalize angle to (0 - 360)
double normalizeAngle(double angle);
