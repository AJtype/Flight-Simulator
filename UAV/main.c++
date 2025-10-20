#include "UAV.hpp"
#include "../Utils/utils.hpp"
#include <iostream>

void check_UAVConstructor();
void check_multiple_UAVConstructors();

int main() {
    // check_UAVConstructor();

    check_multiple_UAVConstructors();

    return 0;
}

void check_UAVConstructor() {
    std::string paramsFile("../SimParams.ini");
    SimParams params;

    std::cout << "\n---testing UAV Constructor---\n" << std::endl;

    parseSimParams(paramsFile, params);

    UAV drone(params, 0);
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

    for (size_t i = 0; i < params.nUav; i++) {
        UAV drone(params, i);
        drones.push_back(std::move(drone));
    }

    for (size_t i = 0; i < params.nUav; i++) {
        std::cout << "drone number " << i << ": " << std::endl;
        drones[i].print();
        std::cout << std::endl;
    }

    std::cout << "\n---end of UAV Constructor test---\n" << std::endl;
}
