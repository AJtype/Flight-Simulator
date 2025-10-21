#include "Utils/utils.hpp"
#include "global_data/SimParams.hpp"
#include "UAV/UAV.c++"
#include <fstream>

int main() {
    std::vector<Command> commands;
    std::string cmdsFile("../SimCmds.txt");
    SimParams params;
    std::vector<UAV> drones;

    // Parse
    if (parseSimParams("../SimParams.ini", params)) {
        std::cout << "error with SimParams.ini" << std::endl;
        return 1;
    } if (parseCommands("../SimCmds.txt", commands)) {
        std::cout << "error with SimCmds.txt" << std::endl;
        return 1;
    }

    // Initialize UAVs
    drones.reserve(params.nUav); // avoid vector reallocation
    for (size_t i = 0; i < params.nUav; i++) {
        drones.emplace_back(params, i);
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

    std::cout << "Simulation completed successfully!" << std::endl;
    std::cout << "Output files: ";
    for (int i = 0; i < params.nUav; ++i) {
        std::cout << "UAV" << i << ".txt ";
    }
    std::cout << std::endl;

    return 0;
}