#pragma once

#include "../SimParams/SimParams.hpp"
#include "../Utils/utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

constexpr double DEGREE_TOLERANCE = 0.02;
constexpr double DISTANCE_TOLERANCE = 0.05;
constexpr double ENTRY_ANGLE_DEG = 45.0;

enum StateOption {
    NEWTARGET = 0,
    CIRCLINGAFTERTARGET = 1,
    ENTERINGCIRCLE = 2,
    CIRCLING = 3
};

class UAV {
private:
    size_t id; // TODO: UAV should assign his own ID
    
    Point curr;
    double curr_z; // currently doesn't change

    Point target;

    double azimuth; // saved in degrees, compared to x axis
    double minRadius; // currently doesn't change
    double v0; // currently doesn't change
    double vx, vy;
    StateOption state;

    std::ofstream outFile;
    
    // helper funcs

    /**
     * @brief Calculates the angular difference between the UAV's heading and the target.
     * @return The angle difference in degrees, measured clockwise
     * from the UAV's current heading. 
     * - 0°   → target is straight ahead
     * - 90°  → target is to the right
     * - 180° → target is behind
     * - 270° → target is to the left
     * @note
     * - `azimuth` is assumed to be in degrees.
     */
    double angleDifferenceToTarget() const; // TODO: test

    /**
     * @brief Updates the UAV's velocity vector based on its current heading.
     * This function calculates the UAV's X and Y velocity components based
     * on its speed and azimuth angle.
     * The azimuth is interpreted in degrees, measured counterclockwise
     * from the positive X-axis.
     */
    void updateVelocity();

    /**
     * @brief Moves the UAV in a straight line based on its current velocity.
     * This function updates the UAV's current position based on the velocity
     * vector over the given time step.
     * @param dt The elapsed time (in seconds) over which to move the UAV. 
     *           Expected to be positive; validation is assumed to be
     *           handled externally.
     * @note 
     * - The velocity components `vx` and `vy` must already reflect the UAV's 
     *   current heading and speed. They are **not updated** within this function.
     */
    void moveStraight(const double dt);

    /**
     * @brief Moves the UAV along a circular path for a given time step.
     * @param dt The elapsed time (in seconds) over which the UAV moves along the circle.
     * @param r  The radius of the circular path.
     */
    void moveCircle(const double dt, const double r);

public:
    // constructors and destructor
    /**
     * @brief Constructs a UAV object with initial simulation parameters.
     * @param params a SimParams struct containing the UAV's initial state
     * @param id     Unique identifier for the UAV (used for logging and identification)
     *
     * @throws std::runtime_error if the output file cannot be opened.
     *
     * @note
     * - The UAV starts in the `CIRCLINGAFTERTARGET` state
     */
    UAV(const SimParams& params, const int id);
    UAV(UAV&&) = default; // allow moving
    UAV& operator=(UAV&&) = default;
    UAV(const UAV&) = delete; // disable copying
    ~UAV();

    /**
     * @brief Sets a new target for the UAV
     * @param t the coordinants of the new target
     *
     * @note
     * - Changes to state to NEWTARGET
     * - makes centerComputed false, because the UAV will start flying straight
     */
    void setTarget(const Point& t);

    /**
     * @brief Updates the UAV's position and angle according to the state and delta time.
     * The function uses tolerances to handle simulation jumps (`DEGREE_TOLERANCE`
     * and `DISTANCE_TOLERANCE`)
     * @param dt The elapsed simulation time (seconds) for this update step.
     * @throws std::out_of_range if the UAV enters an invalid, undefined state.
     */
    void update(const double dt);

    /**
     * @brief Writes the UAV's current location and direction to the output file.
     * The output format is:
     * <time> <x> <y> <azimuth>\n
     * Example:
     * 12.50 103.42  88.10  270.00
     * @param time The current simulation time to record (in seconds).
     */
    void writeOutput(const double time);

    // test funcs
    void print() const;
    int getId() const;
};