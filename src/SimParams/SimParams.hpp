#pragma once
#include "../Utils/utils.hpp"
#include <iostream>
// TODO: change name of file
struct Command  {
    double time;
    int uavId;
    Point target;

    void print() const;
};

struct SimParams {
    double dt;
    int nUav;
    double r0;
    Point start;
    double z0;
    double v0;
    double az;
    double timeLim;

    void print() const;
};

// Parse SimParams.ini from file
bool parseSimParams(const std::string& filename, SimParams& params);

// Parse SimCmds.txt from file
bool parseCommands(const std::string& filename, std::vector<Command>& commands);