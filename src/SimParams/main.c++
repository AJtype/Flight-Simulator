#include "SimParams.hpp"

void testParseSimParams();
void testParseCommands();

int main() {
    testParseSimParams();

    testParseCommands();

    return 0;
}

void testParseSimParams() {
    std::cout << "\n---testing parseSimParams func---\n" << std::endl;

    SimParams params;
    std::string file("../SimParams.ini");

    parseSimParams(file, params);

    params.print();
    
    std::cout << "\n---end of parseSimParams test---\n" << std::endl;
}

void testParseCommands() {
    std::cout << "\n---testing parseCommands func---\n" << std::endl;

    std::vector<Command> commands;
    std::string file("../SimCmds.txt");

    parseCommands(file, commands);

    for (auto command : commands) {
        command.print();
        std::cout << std::endl;
    }

    std::cout << "\n---end of parseCommands test---\n" << std::endl;
}
