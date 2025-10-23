#include "utils.hpp"

void trim(std::string& s) {
    // Remove leading spaces/tabs
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t'))
        s.erase(s.begin());

    // Remove trailing spaces/tabs
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t'))
        s.pop_back();
}

double degToRad(const double deg) {
    return deg * PI / 180.0;
}

double radToDeg(const double rad) {
    return rad * 180.0 / PI;
}

double normalizeAngle(double angle) {
    while (angle < 0) angle += 360.0;
    while (angle >= 360.0) angle -= 360.0;
    return angle;
}

double calcDistance(const Point& here, const Point& there) {
    double dx = here.x - there.x;
    double dy = here.y - there.y;
    return std::sqrt(dx * dx + dy * dy);
}
