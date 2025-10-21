#include "UAV.hpp"
#include "../Utils/utils.hpp"
#include <iostream>

void check_UAVConstructor();
void check_multiple_UAVConstructors();
void check_setTarget();

int main() {
    // check_UAVConstructor();

    // check_multiple_UAVConstructors();

    check_setTarget();

    return 0;
}

void check_UAVConstructor() {
    std::string paramsFile("../SimParams.ini");
    SimParams params;

    std::cout << "\n---testing UAV Constructor---\n" << std::endl;

    parseSimParams(paramsFile, params);

    // initialize UAV
    UAV drone(params, 0);

    // print UAV params
    std::cout << "first drone = " << std::endl;
    drone.print();

    std::cout << "\n---end of UAV Constructor test---\n" << std::endl;
}

void check_multiple_UAVConstructors() {
    std::string paramsFile("../SimParams.ini");
    SimParams params;
    std::vector<UAV> drones;

    std::cout << "\n---testing UAV Constructor---\n" << std::endl;

    parseSimParams(paramsFile, params);

    // initialize UAVs
    drones.reserve(params.nUav); // avoid vector reallocation
    for (size_t i = 0; i < params.nUav; i++) {
        drones.emplace_back(params, i);
    }

    // print UAVs params
    for (size_t i = 0; i < params.nUav; i++) {
        std::cout << "drone number " << i << ": " << std::endl;
        drones[i].print();
        std::cout << std::endl;
    }

    std::cout << "\n---end of UAV Constructor test---\n" << std::endl;
}

void check_setTarget() {
    std::string paramsFile("../SimParams.ini");
    SimParams params;
    std::vector<UAV> drones;

    std::cout << "\n---testing set_target func---\n" << std::endl;

    parseSimParams(paramsFile, params);

    // initialize UAVs
    drones.reserve(params.nUav); // avoid vector reallocation
    for (size_t i = 0; i < params.nUav; i++) {
        drones.emplace_back(params, i);
    }

    drones[0].setTarget(10, 10.5);

    // print UAVs params
    for (size_t i = 0; i < params.nUav; i++) {
        std::cout << "drone number " << i << ": " << std::endl;
        drones[i].print();
        std::cout << std::endl;
    }

    std::cout << "\n---end of set_target test---\n" << std::endl;
}
