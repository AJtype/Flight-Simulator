#pragma once
#include <iostream>
#include <fstream>

class UAV { // TODO
private:
    double curr_x;
    double curr_y;
    double curr_z;
    size_t id;
    double target_x;
    double target_y;
    double azimuth;
    bool isCircling;
    std::ofstream outFile;
};