/*
Class functions used for robot arm manipulations

Author: Billal Rahimi
Email: billalrahimi@hotmail.com

Date: 2022-07-29
*/

#include "robotArm.hpp"

// Constructor
Arm::Arm()
{

}

/**
 * Homogenous Matrix based on standard robotics pose vector notation
 * Function is used to create a robot arm link.
 * 
 * Pose notation:
 * T = [R t]
 *     [0 1]
 * 
 * @param rx x rotation, roll (°)
 * @param ry y rotation, pitch (°)
 * @param rz z rotation, yaw (°)
 * @param tx x translation (mm)
 * @param ty y translation (mm)
 * @param tz z translation (mm)
 * @return 4x4 matrice that reflects the pose coordinates
 */
std::vector<std::vector<float>> Arm::createLink(float rx, float ry, float rz, float tx, float ty, float tz)
{
    // Multi-dimensional vector
    std::vector<std::vector<float>> Link = {
        {cos(rz) * cos(ry), cos(rz) * sin(ry) * sin(rx) - sin(rz) * cos(rx), cos(rz) * sin(ry) * cos(rx) + sin(rz) * sin(rx), tx},
        {sin(rz) * cos(ry), sin(rz) * sin(ry) * sin(rx) + cos(rz) * cos(rx), sin(rz) * sin(ry) * cos(rx) - cos(rz) * sin(rx), ty},
        {(float)-1.0 * sin(ry), cos(ry) * sin(rx), cos(ry) * cos(rx), tz}
        };

    return Link;
}


// Deconstructor
Arm::~Arm()
{

}