#pragma once
#include <iostream>
// TODO: change name of file
struct Command  {
    double time;
    int uavId;
    double x;
    double y;

    void print() const;
};

struct SimParams {
    double dt;
    int nUav;
    double r0;
    double x0;
    double y0;
    double z0;
    double v0;
    double az;
    double timeLim;

    void print() const;
};
