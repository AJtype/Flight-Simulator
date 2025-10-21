#include "UAV.hpp"

void UAV::updateVelocity() {
    double azRad = degToRad(azimuth);
    vx = v0 * cos(azRad);
    vy = v0 * sin(azRad);
}

UAV::UAV(const SimParams &params, const int id)
    : id(id), curr_x(params.x0), curr_y(params.y0), curr_z(params.z0),
      v0(params.v0), minRadius(params.r0), azimuth(params.az),
      target_x(params.x0), target_y(params.y0), target_z(params.z0),
      isCircling(true) {
    updateVelocity();
    std::string filename = "UAV" + std::to_string(id) + ".txt";
    outFile.open(filename);
}

UAV::~UAV() {
    if (outFile.is_open())
        outFile.close();
}

void UAV::print() const {
    std::cout << "UAV.id = " << id << std::endl;
    std::cout << "UAV.curr_x = " << curr_x << std::endl;
    std::cout << "UAV.curr_y = " << curr_y << std::endl;
    std::cout << "UAV.curr_z = " << curr_z << std::endl;
    std::cout << "UAV.target_x = " << target_x << std::endl;
    std::cout << "UAV.target_y = " << target_y << std::endl;
    std::cout << "UAV.target_z = " << target_z << std::endl;
    std::cout << "UAV.azimuth = " << azimuth << std::endl;
    std::cout << "UAV.minRadius = " << minRadius << std::endl;
    std::cout << "UAV.velocity = " << v0 << std::endl;
    std::cout << "UAV.vx = " << vx << "\tUAV,vy = " << vy << std::endl;
    std::cout << "UAV.isCircling = " << isCircling << std::endl;
}

int UAV::getId() const {
    return id;
}

void UAV::setTarget(double tx, double ty)
{
    target_x = tx;
    target_y = ty;
    isCircling = false;
}

// currently only works in a straight line TODO: add complexity
void UAV::update(const double dt) {
    curr_x= vx * dt;
    curr_y += vy * dt;
}

void UAV::writeOutput(const double time) {
    if (outFile.is_open()) {
        outFile << std::fixed << std::setprecision(2)
                << time << " " << curr_x << " " << curr_y << " " << azimuth << "\n";
    }
}
