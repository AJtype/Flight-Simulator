#pragma once

#include "../global_data/SimParams.hpp"
#include "../Utils/utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class UAV { // TODO
private:
    size_t id; // TODO: UAV should assign his own ID
    
    double curr_x;
    double curr_y;
    double curr_z;

    double target_x;
    double target_y;
    double target_z; // currently doesn't change

    double azimuth; // TODO: in what format is this saved?
    double minRadius; // currently doesn't change
    double v0; // currently doesn't change // TODO: might change with vx and vy
    double vx, vy;
    bool isCircling;

    std::ofstream outFile;

    void updateVelocity();

public:
    UAV(const SimParams &params, const int id);
    UAV(UAV&&) = default; // allow moving
    UAV& operator=(UAV&&) = default;
    UAV(const UAV&) = delete; // disable copying
    ~UAV();

    void setTarget(double tx, double ty);

    void print() const;
};