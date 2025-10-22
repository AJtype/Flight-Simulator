#pragma once

#include "../global_data/SimParams.hpp"
#include "../Utils/utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

constexpr double TOLERANCE = 0.02;

enum StateOption {
    NEWTARGET = 0,
    CIRCLINGAFTERTARGET = 1,
    ENTERINGCIRCLE = 2,
    CIRCLING = 3
};

class UAV { // TODO
private:
    size_t id; // TODO: UAV should assign his own ID
    
    Point curr;
    double curr_z;

    Point target;

    double azimuth; // TODO: in what format is this saved?
    double minRadius; // currently doesn't change
    double v0; // currently doesn't change // TODO: might change with vx and vy
    double vx, vy;
    StateOption state;

    bool centerComputed;
    Point center;

    bool passed;

    std::ofstream outFile;

    void updateVelocity();

    void moveStraight(const double dt);
    void moveCircle(const double dt, const double r);

    void computeCenter(const double r);

    double angleDifferenceToTarget() const; // TODO: test

public:
    UAV(const SimParams &params, const int id);
    UAV(UAV&&) = default; // allow moving
    UAV& operator=(UAV&&) = default;
    UAV(const UAV&) = delete; // disable copying
    ~UAV();

    void print() const;
    int getId() const;
    void setTarget(double tx, double ty);

    void update(const double dt);
    void writeOutput(const double time);
};