#include "../src/Utils/utils.hpp"
#include <iostream>
#include <assert.h>

void testDegToRad();
void testRadToDeg();
void testNormalizeAngle();
void testCalcDistance();

int main() {
    testDegToRad();

    testRadToDeg();

    testNormalizeAngle();

    testCalcDistance();

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

void testCalcDistance() {
    std::cout << "\n---testing normalizeAngle func---\n" << std::endl;
    
    // Test 1: Distance between the same point should be 0
    Point a{0, 0};
    Point b{0, 0};
    assert(calcDistance(a, b) == 0.0);

    // Test 2: Distance along x-axis
    Point c{3, 0};
    Point d{0, 0};
    assert(calcDistance(c, d) == 3.0);

    // Test 3: Distance along y-axis
    Point e{0, 4};
    Point f{0, 0};
    assert(calcDistance(e, f) == 4.0);

    // Test 4: Distance diagonally (3-4-5 triangle)
    Point g{3, 4};
    Point h{0, 0};
    assert(calcDistance(g, h) == 5.0);

    // Test 5: Distance between arbitrary points
    Point i{1.5, 2.5};
    Point j{4.5, 6.5};
    assert(std::abs(calcDistance(i, j) - 5.0) < 1e-9); // use epsilon for floating point

    std::cout << "\n---end of normalizeAngle test---\n" << std::endl;
}
