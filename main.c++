#include "Utils/utils.hpp"
#include "SimParams/SimParams.hpp"
#include "UAV/UAV.hpp"
#include <fstream>

int main() {
    std::vector<Command> commands;
    SimParams params;
    std::vector<UAV> drones;

    // Parse
    if (!parseSimParams("SimParams.ini", params)) {
        std::cout << "error with SimParams.ini" << std::endl;
        return 1;
    } if (!parseCommands("SimCmds.txt", commands)) {
        std::cout << "error with SimCmds.txt" << std::endl;
        return 1;
    }

    // Initialize UAVs
    drones.reserve(params.nUav); // avoid vector reallocation
    for (size_t i = 0; i < params.nUav; i++) {
        drones.emplace_back(params, i);
    }

    size_t cmdIndex = 0;
    for (double currentTime = 0.0; currentTime <= params.timeLim; currentTime += params.dt) {
        while (cmdIndex < commands.size() && 
         commands[cmdIndex].time <= currentTime) {
            int uavId = commands[cmdIndex].uavId;
            if (uavId < 0 || uavId >= params.nUav)
                std::cout << "invalid ID";
            else
                drones[uavId].setTarget(commands[cmdIndex].target);
            cmdIndex++;
        }

        for (auto& uav : drones) {
            uav.update(params.dt);
            uav.writeOutput(currentTime);
        }
    }

    std::cout << "Simulation completed successfully!" << std::endl;
    std::cout << "Output files: ";
    for (int i = 0; i < params.nUav; ++i) {
        std::cout << "UAV" << i << ".txt ";
    }
    std::cout << std::endl;

    return 0;
}