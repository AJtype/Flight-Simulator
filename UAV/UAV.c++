#include "UAV.hpp"

void UAV::updateVelocity() {
    double azRad = degToRad(azimuth);
    vx = v0 * cos(azRad);
    vy = v0 * sin(azRad);
}

void UAV::moveStraight(const double dt) {
    curr_x += vx * dt;
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
    updateVelocity();

    // Position angle is 90° offset from heading (CW flight)
    double posAngle = degToRad(azimuth - 90);

    // Move along circle path
    moveStraight(dt);
}

void UAV::computeCenter(const double r) {
    double angle_rad = degToRad(azimuth + 90.0); // 90° to the right for CW center
    center_x = curr_x + r * cos(angle_rad);
    center_y = curr_y + r * sin(angle_rad);
    centerComputed = true;
}

double UAV::angleDifferenceToTarget() const {
    // Compute angle from UAV to target
    double dx = curr_x - target_x;
    double dy = curr_y - target_y;
    double targetAngle = normalizeAngle(radToDeg(atan2(dy, dx)));

    // Difference from current azimuth
    return normalizeAngle(targetAngle - azimuth); // 0–360 degrees, clockwise positive
}

UAV::UAV(const SimParams &params, const int id)
    : id(id), curr_x(params.x0), curr_y(params.y0), curr_z(params.z0),
      v0(params.v0), minRadius(params.r0), azimuth(params.az),
      target_x(params.x0), target_y(params.y0),
      state(CIRCLINGAFTERTARGET), centerComputed(false), passed(false) {
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
    std::cout << "UAV.isCircling = " << state << std::endl;
}

int UAV::getId() const {
    return id;
}

void UAV::setTarget(double tx, double ty) {
    target_x = tx;
    target_y = ty;
    state = NEWTARGET;
}

// stages CIRCLINGAFTERTARGET and CIRCLING
void UAV::update(const double dt) {
    switch (state) {
    case NEWTARGET:
        /* if (encounter in middle of dt) {
            calculate rest of dt
            update(first part of dt)
            state = CIRCLINGAFTERTARGET;
            update(last part of dt)
            return;
        }*/
        /*
        if (aiming at target) {
            centerComputed = false;
            moveStraight(dt);
            return;
        }
        moveCircle(dt, minRadius);
        */
        std::cout << "entered state NEWTARGET" << std::endl;
        exit(1);
        break;
    case CIRCLINGAFTERTARGET:
        /* if (encounter in middle of dt) { // complex solution
            calculate dt split
            update(first part of dt)
            state = ENTERINGCIRCLE;
            update(last part of dt)
            return;
        }*/ 
       moveCircle(dt, minRadius);

       if (fabs(angleDifferenceToTarget() - 135.0) < TOLERANCE) {
            state = ENTERINGCIRCLE;
            centerComputed = false;
       }

       break;
    case ENTERINGCIRCLE:
        /*if (distance from target == minRadius) {
            state == CIRCLING
        }*/

        moveStraight(dt);
        
        break;
    case CIRCLING:
        moveCircle(dt, minRadius);
        break;
    default:
        std::cout << "entered non-existing state" << std::endl;
        break;
    }
}

void UAV::writeOutput(const double time) {
    if (outFile.is_open()) {
        outFile << std::fixed << std::setprecision(2)
                << time << " " << curr_x << " " << curr_y << " " << azimuth << "\n";
    }
}
