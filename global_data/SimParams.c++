#include "SimParams.hpp"

void SimParams::print() {
    std::cout << "params.dt = " << dt << std::endl;
    std::cout << "params.nUav = " << nUav << std::endl;
    std::cout << "params.r = " << r << std::endl;
    std::cout << "params.x0 = " << x0 << std::endl;
    std::cout << "params.y0 = " << y0 << std::endl;
    std::cout << "params.z0 = " << z0 << std::endl;
    std::cout << "params.v0 = " << v0 << std::endl;
    std::cout << "params.az = " << az << std::endl;
    std::cout << "params.timeLim = " << timeLim << std::endl;
}

void Command::print() {
    std::cout << "commands.time = " << time << std::endl;
    std::cout << "commands.nUav = " << uavId << std::endl;
    std::cout << "commands.x = " << x << std::endl;
    std::cout << "commands.y = " << y << std::endl;
}
