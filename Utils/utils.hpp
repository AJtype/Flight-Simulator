#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

const double PI = 3.14159265358979323846;

struct Point {
    double x, y;
};

void trim(std::string& s);

// Convert degrees to radians
double degToRad(const double deg);

// Convert radians to degrees
double radToDeg(const double rad);

// Normalize angle to (0 - 360)
double normalizeAngle(double angle);
