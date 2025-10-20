#pragma once
#include <iostream>
// TODO: change name of file
struct Command  {
    double time;
    int uavId;
    double x;
    double y;

    void print();
};

struct SimParams {
    double dt;
    int nUav;
    double r;
    double x0;
    double y0;
    double z0;
    double v0;
    double az;
    double timeLim;

    void print();
};
