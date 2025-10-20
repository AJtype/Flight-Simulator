#pragma once

#include "../global_data/SimParams.hpp"
#include <iostream>
#include <fstream>
#include <string>

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
    double velocity; // currently doesn't change // TODO: might change with vx and vy
    bool isCircling;

    std::ofstream outFile;

public:
    UAV(const SimParams &params, const int id);
    UAV(UAV&&) = default; // allow moving
    UAV& operator=(UAV&&) = default;
    UAV(const UAV&) = delete; // disable copying

    ~UAV();

    void print() const;
};