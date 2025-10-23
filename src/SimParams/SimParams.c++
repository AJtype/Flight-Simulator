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
        trim(line);
        if (line.empty() || line[0] == '#') continue;

        size_t pos = line.find('=');
        if (pos == std::string::npos) { // no equal sign found
            std::cerr << "Warning: Ignoring invalid line (no '='): " << line << std::endl;
            continue; 
        }

        // Split into key and value
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        trim(key);
        trim(value);

        // Assign values (stod = string to double, stoi = string to integer)
        try {
            if (key == "Dt") {
                params.dt = std::stod(value);
                if (params.dt <= 0) throw std::out_of_range("Dt must be positive");
            }
            else if (key == "N_uav") {
                params.nUav = std::stoi(value);
                if (params.nUav <= 0) throw std::out_of_range("N_uav must be positive");
            }
            else if (key == "R") {
                params.r0 = std::stod(value);
                if (params.r0 <= 0) throw std::out_of_range("R must be positive");
            }
            else if (key == "X0") {
                params.start.x = std::stod(value);
            }
            else if (key == "Y0") {
                params.start.y = std::stod(value);
            }
            else if (key == "Z0") {
                params.z0 = std::stod(value);
                if (params.z0 <= 0) throw std::out_of_range("z0 must be positive");
            }
            else if (key == "V0") {
                params.v0 = std::stod(value);
                if (params.v0 < 0) throw std::out_of_range("V0 cannot be negative");
            }
            else if (key == "Az") {
                params.az = std::stod(value);
                if (params.az < 0 || params.az >= 360) throw std::out_of_range("Az must be in [0,360]");
            }
            else if (key == "TimeLim") {
                params.timeLim = std::stod(value);
                if (params.timeLim <= 0) throw std::out_of_range("TimeLim must be positive");
            }
            else {
                std::cerr << "Warning: Unknown key ignored: " << key << std::endl;
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Error: Invalid value for " << key << ": " << value << std::endl;
            return false;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: " << key << " out of range: " << value
                      << " (" << e.what() << ")" << std::endl;
            return false;
        }
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
    size_t lineNumber = 0;
    while (file >> cmd.time >> cmd.uavId >> cmd.target.x >> cmd.target.y) { // Can fail silently
        ++lineNumber;

        // Validate command values
        if (cmd.time < 0) {
            std::cerr << "Error: Command time must be non-negative at line " << lineNumber << std::endl;
            return false;
        }
        if (cmd.uavId < 0) {
            std::cerr << "Error: UAV ID cannot be negative at line " << lineNumber << std::endl;
            return false;
        }

        commands.push_back(cmd);
    }

    // Check if the loop exited due to a format error (not EOF)
    if (!file.eof()) { // Catches if the previous while was exited early
        std::cerr << "Error: Invalid command format at line " << (lineNumber + 1) << std::endl;
        return false;
    }

    file.close();

    // Sort commands by time
    std::sort(commands.begin(), commands.end(),
              [](const Command& a, const Command& b) { return a.time < b.time; });

    return true;
}
