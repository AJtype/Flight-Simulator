#pragma once
#include <iostream>
#include <fstream>

class UAV { // TODO
private:
    size_t id;
    
    double curr_x;
    double curr_y;
    double curr_z;

    double target_x;
    double target_y;
    double target_z; // currently doesn't change

    double azimuth; // TODO: in what format is this saved?
    double minRadius; // currently doesn't change
    double velocity; // currently doesn't change
    bool isCircling;

    std::ofstream outFile;
};