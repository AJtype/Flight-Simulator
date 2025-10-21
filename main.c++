#include "Utils/utils.hpp"
#include "global_data/SimParams.hpp"
#include "UAV/UAV.c++"
#include <fstream>

int main() {
    std::vector<Command> commands;
    std::string paramsFile("../SimParams.ini");
    std::string cmdsFile("../SimCmds.txt");
    SimParams params;
    std::vector<UAV> drones;

    // inits
    parseSimParams(paramsFile, params);
    parseCommands(cmdsFile, commands);

    drones.reserve(params.nUav); // avoid vector reallocation
    for (size_t i = 0; i < params.nUav; i++) {
        drones.emplace_back(params, i);
    }
    

    return 0;
}