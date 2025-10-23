#include "SimParams.hpp"

void Command::print() const {
    std::cout << "commands.time = " << time << std::endl;
    std::cout << "commands.nUav = " << uavId << std::endl;
    std::cout << "commands.x = " << target.x << std::endl;
    std::cout << "commands.y = " << target.y << std::endl;
}

void SimParams::print() const {
    std::cout << "params.dt = " << dt << std::endl;
    std::cout << "params.nUav = " << nUav << std::endl;
    std::cout << "params.r0 = " << r0 << std::endl;
    std::cout << "params.start.x = " << start.x << std::endl;
    std::cout << "params.start.y = " << start.y << std::endl;
    std::cout << "params.z0 = " << z0 << std::endl;
    std::cout << "params.v0 = " << v0 << std::endl;
    std::cout << "params.az = " << az << std::endl;
    std::cout << "params.timeLim = " << timeLim << std::endl;
}

bool parseSimParams(const std::string &filename, SimParams &params) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove whitespace and ignore blank/comment lines
        if (line.empty() || line[0] == '#') continue;

        size_t pos = line.find('=');
        if (pos == std::string::npos) continue; // no equal sign found

        // Split into key and value
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        trim(key);
        trim(value);

        // Assign values (stod = string to double, stoi = string to integer)
        if (key == "Dt") params.dt = std::stod(value);
        else if (key == "N_uav") params.nUav = std::stoi(value);
        else if (key == "R") params.r0 = std::stod(value);
        else if (key == "X0") params.start.x = std::stod(value);
        else if (key == "Y0") params.start.y = std::stod(value);
        else if (key == "Z0") params.z0 = std::stod(value);
        else if (key == "V0") params.v0 = std::stod(value);
        else if (key == "Az") params.az = std::stod(value);
        else if (key == "TimeLim") params.timeLim = std::stod(value);
    }

    if (file.is_open())
        file.close();

    return true;
}

bool parseCommands(const std::string &filename, std::vector<Command> &commands) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        return false;
    }

    Command cmd;
    while (file >> cmd.time >> cmd.uavId >> cmd.target.x >> cmd.target.y) {
        commands.push_back(cmd);
    }
    file.close();

    // Sort commands by time
    std::sort(commands.begin(), commands.end(),
              [](const Command& a, const Command& b) { return a.time < b.time; });
    
    return true;
}