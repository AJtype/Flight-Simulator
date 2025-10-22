#include "UAV.hpp"

void UAV::updateVelocity() {
    double azRad = degToRad(azimuth);
    vx = v0 * cos(azRad);
    vy = v0 * sin(azRad);
}

void UAV::moveStraight(const double dt) {
    curr_x= vx * dt;
    curr_y += vy * dt;
}

void UAV::moveCircle(const double dt, const double r) {
    // Compute center of circle
    if (!centerComputed) {
        computeCenter(r);
    }

    // Angular velocity (negative for CW)
    double angularV = -v0 / r;

    // Update azimuth (convert omega*dt to degrees)
    azimuth = normalizeAngle(azimuth + radToDeg(angularV * dt));

    // Update velocity vectors
    vx = v0 * cos(degToRad(azimuth));
    vy = v0 * sin(degToRad(azimuth));

    // Move along circle path
    curr_x = center_x + r * cos(degToRad(azimuth));
    curr_y = center_y + r * sin(degToRad(azimuth));
}

void UAV::computeCenter(const double r) {
    double angle_rad = degToRad(azimuth + 90.0); // 90° to the right for CW center
    center_x = curr_x + r * cos(angle_rad);
    center_y = curr_y + r * sin(angle_rad);
    centerComputed = true;
}

UAV::UAV(const SimParams &params, const int id)
    : id(id), curr_x(params.x0), curr_y(params.y0), curr_z(params.z0),
      v0(params.v0), minRadius(params.r0), azimuth(params.az),
      target_x(params.x0), target_y(params.y0),
      isCircling(true), centerComputed(false) {
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
    moveCircle(dt, minRadius);
}

void UAV::writeOutput(const double time) {
    if (outFile.is_open()) {
        outFile << std::fixed << std::setprecision(2)
                << time << " " << curr_x << " " << curr_y << " " << azimuth << "\n";
    }
}
