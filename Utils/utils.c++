#include "utils.hpp"

void trim(std::string& s) {
    // Remove leading spaces/tabs
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t'))
        s.erase(s.begin());

    // Remove trailing spaces/tabs
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t'))
        s.pop_back();
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
        if (pos == std::string::npos) continue; // no equal sign found // TODO: add error handling

        // Split into key and value
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        trim(key);
        trim(value);

        // Assign values (stod = string to double, stoi = string to integer)
        if (key == "Dt") params.dt = std::stod(value);
        else if (key == "N_uav") params.nUav = std::stoi(value);
        else if (key == "R") params.r = std::stod(value);
        else if (key == "X0") params.x0 = std::stod(value);
        else if (key == "Y0") params.y0 = std::stod(value);
        else if (key == "Z0") params.z0 = std::stod(value);
        else if (key == "V0") params.v0 = std::stod(value);
        else if (key == "Az") params.az = std::stod(value);
        else if (key == "TimeLim") params.timeLim = std::stod(value);
    }

    return true;
}
