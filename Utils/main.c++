#include "utils.hpp"

void testDegToRad();
void testRadToDeg();
void testNormalizeAngle();

int main() {
    testDegToRad();

    testRadToDeg();

    testNormalizeAngle();

    return 0;
}

void testDegToRad() {
    std::cout << "\n---testing degToRad func---\n" << std::endl;

    if (0.0 != degToRad(0.0))
        std::cout << "FAILED on degToRad(0.0)" << std::endl;
    if (PI != degToRad(180.0))
        std::cout << "FAILED on degToRad(180.0)" << std::endl;
    if ((2 * PI) != degToRad(360.0))
        std::cout << "FAILED on degToRad(360.0)" << std::endl;
    if ((PI / 2) != degToRad(90.0))
        std::cout << "FAILED on degToRad(90.0)" << std::endl;

    std::cout << "\n---end of degToRad test---\n" << std::endl;
}

void testRadToDeg() {
    std::cout << "\n---testing radToDeg func---\n" << std::endl;

    if (0.0 != radToDeg(0.0))
        std::cout << "FAILED on radToDeg(0.0)" << std::endl;
    if (180.0 != radToDeg(PI))
        std::cout << "FAILED on radToDeg(PI)" << std::endl;
    if (360.0 != radToDeg(2 * PI))
        std::cout << "FAILED on radToDeg(2 * PI)" << std::endl;
    if (90.0 != radToDeg(PI / 2))
        std::cout << "FAILED on radToDeg(PI / 2)" << std::endl;
    
    std::cout << "\n---end of radToDeg test---\n" << std::endl;
}

void testNormalizeAngle() {
    std::cout << "\n---testing normalizeAngle func---\n" << std::endl;

    if (0.0 != normalizeAngle(0.0))
        std::cout << "FAILED on normalizeAngle(0.0)" << std::endl;
    if (0.0 != normalizeAngle(360.0))
        std::cout << "FAILED on normalizeAngle(360.0)" << std::endl;
    if (0.0 != normalizeAngle(720.0))
        std::cout << "FAILED on normalizeAngle(720.0)" << std::endl;
    if (270.0 != normalizeAngle(-90.0))
        std::cout << "FAILED on normalizeAngle(-90.0)" << std::endl;
    if (90.0 != normalizeAngle(450.0))
        std::cout << "FAILED on normalizeAngle(450.0)" << std::endl;
    
    std::cout << "\n---end of normalizeAngle test---\n" << std::endl;
}
