#include "Utils/utils.hpp"
#include "global_data/SimParams.hpp"
#include <fstream>

int main() {
    std::vector<Command> commands;
    std::string paramsFile("../SimParams.ini");
    std::string cmdsFile("../SimCmds.txt");
    SimParams params;

    // inits
    parseSimParams(paramsFile, params);
    parseCommands(cmdsFile, commands);

    return 0;
}