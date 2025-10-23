#include "../src/UAV/UAV.hpp"
#include "../src/Utils/utils.hpp"
#include <iostream>

void check_UAVConstructor();
void check_multiple_UAVConstructors();
void check_setTarget();
void check_basicLoop();
void check_loopWithCmds();

// more UAV will be created, but only the amount in SimsParams will get the Commands
int main() {
    check_loopWithCmds();

    check_basicLoop();

    check_UAVConstructor();

    check_multiple_UAVConstructors();

    check_setTarget();

    return 0;
}

void check_UAVConstructor() {
    std::string paramsFile("../SimParams.ini");
    SimParams params;

    std::cout << "\n---testing UAV Constructor---\n" << std::endl;

    parseSimParams(paramsFile, params);

    // initialize UAV
    UAV drone(params);

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
        drones.emplace_back(params);
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
        drones.emplace_back(params);
    }

    Point newTarget = {10, 10.5};
    drones[0].setTarget(newTarget);

    // print UAVs params
    for (size_t i = 0; i < params.nUav; i++) {
        std::cout << "drone number " << i << ": " << std::endl;
        drones[i].print();
        std::cout << std::endl;
    }

    std::cout << "\n---end of set_target test---\n" << std::endl;
}

void check_basicLoop() {
    std::string paramsFile("../SimParams.ini");
    SimParams params;
    std::vector<UAV> drones;

    std::cout << "\n---testing main loop---\n" << std::endl;

    parseSimParams(paramsFile, params);

    // initialize UAVs
    drones.reserve(params.nUav); // avoid vector reallocation
    for (size_t i = 0; i < params.nUav; i++) {
        drones.emplace_back(params);
    }

    // Simulation loop
    double currentTime = 0.0;
    while (currentTime <= params.timeLim) {
        // Update all UAVs
        for (auto &uav : drones) {
            uav.update(params.dt);
            uav.writeOutput(currentTime);
        } currentTime += params.dt;
    }
    
    std::cout << "\n---end of main loop test---\n" << std::endl;
}

void check_loopWithCmds() {
    std::string paramsFile("../SimParams.ini");
    std::string file("../SimCmds.txt");
    SimParams params;
    std::vector<UAV> drones;
    std::vector<Command> commands;

    std::cout << "\n---testing main loop---\n" << std::endl;

    parseSimParams(paramsFile, params);
    parseCommands(file, commands);

    // initialize UAVs
    drones.reserve(params.nUav); // avoid vector reallocation
    for (size_t i = 0; i < params.nUav; i++) {
        drones.emplace_back(params);
    }

    // Simulation loop
    double currentTime = 0.0;
    size_t cmdIndex = 0;
    while (currentTime <= params.timeLim) {
        while (cmdIndex < commands.size() && 
         commands[cmdIndex].time <= currentTime) {
            int uavId = commands[cmdIndex].uavId;
            if (uavId < 0 || uavId >= params.nUav)
                std::cout << "invalid ID";
            else
                drones[uavId].setTarget(commands[cmdIndex].target);
            cmdIndex++;
        }

        // Update all UAVs
        for (auto &uav : drones) {
            uav.update(params.dt);
            uav.writeOutput(currentTime);
        } currentTime += params.dt;
    }
    
    std::cout << "\n---end of main loop test---\n" << std::endl;
}
