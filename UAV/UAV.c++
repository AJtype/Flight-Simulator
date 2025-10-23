#include "UAV.hpp"

UAV::UAV(const SimParams& params, const int id)
    : id(id), 
      curr{params.start.x, params.start.y},
      curr_z(params.z0),
      v0(params.v0),
      minRadius(params.r0),
      azimuth(params.az),
      target{params.start.x, params.start.y},
      state(CIRCLINGAFTERTARGET) {
    updateVelocity();

    std::string filename = "UAV" + std::to_string(id) + ".txt";
    outFile.open(filename);
    if (!outFile.is_open())
        throw std::runtime_error("Failed to open UAV output file: " + filename);
}

UAV::~UAV() {
    if (outFile.is_open())
        outFile.close();
}

double UAV::angleDifferenceToTarget() const {
    // Compute angle from UAV to target
    double dx = target.x - curr.x;
    double dy = target.y - curr.y;
    double targetAngle = normalizeAngle(radToDeg(atan2(dy, dx)));

    // Difference from current azimuth
    return normalizeAngle(azimuth - targetAngle); // 0–360 degrees, clockwise positive
}

void UAV::updateVelocity() {
    double azRad = degToRad(azimuth);
    vx = v0 * cos(azRad);
    vy = v0 * sin(azRad);
}

void UAV::moveStraight(const double dt) {
    curr.x += vx * dt;
    curr.y += vy * dt;
}

void UAV::moveCircle(const double dt, const double r) {
    // Angular velocity (negative for CW)
    double angularV = -v0 / r;

    // Update azimuth (convert omega*dt to degrees)
    azimuth = normalizeAngle(azimuth + radToDeg(angularV * dt));
    updateVelocity();

    // Move along circle path
    moveStraight(dt);
}

void UAV::setTarget(const Point& t) {
    target = t;
    state = NEWTARGET;
}

void UAV::update(const double dt) {
    switch (state) {
    case NEWTARGET:
        if (fabs(angleDifferenceToTarget()) > DEGREE_TOLERANCE) { // if not looking at target
            moveCircle(dt, minRadius);
            break;
        } // else (looking at target)
        moveStraight(dt);
        
        // check if got to target
        if (calcDistance(curr, target) < DISTANCE_TOLERANCE) { // can miss because of jumps (dt) and TOLERANCE
            state = CIRCLINGAFTERTARGET;
        }
        
        break;
    case CIRCLINGAFTERTARGET: // do 3/4 circle to head toward circle around target
       moveCircle(dt, minRadius);

        // check if ready to enter circle
       if (fabs(angleDifferenceToTarget() - ENTRY_ANGLE_DEG) < DEGREE_TOLERANCE) { // can miss because of jumps (dt) and TOLERANCE
            state = ENTERINGCIRCLE;
       }

       break;
    case ENTERINGCIRCLE: // enter circle around target
        moveStraight(dt);

        // check if entered circle (at radius distance from the center)
        if (fabs(calcDistance(curr, target) - minRadius) < DISTANCE_TOLERANCE) { // can miss because of jumps (dt) and TOLERANCE
            state = CIRCLING;
        }
        
        break;
    case CIRCLING: // circle around target :D
        moveCircle(dt, minRadius);
        break;
    default:
        throw std::out_of_range("UAV non-existing state");
        break;
    }
}

void UAV::writeOutput(const double time) {
    if (!outFile.is_open())
        return;
    outFile << std::fixed << std::setprecision(2)
        << time << " " << curr.x << " " << curr.y << " " << azimuth << "\n";
}

void UAV::print() const {
    std::cout << "UAV.id = " << id << std::endl;
    std::cout << "UAV.curr.x = " << curr.x << std::endl;
    std::cout << "UAV.curr.y = " << curr.y << std::endl;
    std::cout << "UAV.curr_z = " << curr_z << std::endl;
    std::cout << "UAV.target.x = " << target.x << std::endl;
    std::cout << "UAV.target.y = " << target.y << std::endl;
    std::cout << "UAV.azimuth = " << azimuth << std::endl;
    std::cout << "UAV.minRadius = " << minRadius << std::endl;
    std::cout << "UAV.velocity = " << v0 << std::endl;
    std::cout << "UAV.vx = " << vx << "\tUAV,vy = " << vy << std::endl;
    std::cout << "UAV.state = " << state << std::endl;
}

int UAV::getId() const {
    return id;
}
