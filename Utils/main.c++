#include "utils.hpp"

void check_parseSimParams();

int main() {
    check_parseSimParams();

    return 0;
}

void check_parseSimParams() {
    SimParams params;
    std::string file("../SimParams.ini");

    parseSimParams(file, params);

    params.printSimParams();
}
