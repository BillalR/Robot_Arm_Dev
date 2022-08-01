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
    // TODO --> Create an initializer that reads current servo values
    // Assign link initial values
    armJointVec[0] = {createLink(0, 0, 0, 0, 0, 0)};
    armJointVec[1] = {createLink(0, 0, 200, 0, 0, 0)};
    armJointVec[2] = {createLink(0, 100, 0, 0, 0, 0)};
    armJointVec[3] = {createLink(100, 0, 0, 0, 0, 0)};
}

void Arm::printVector()
{
    unsigned short int n = armJointVec.size();
    unsigned short int M = armJointVec[0].size();
    unsigned short int N = armJointVec[0][0].size();

    for(unsigned short int i = 0; i < n; i++)
    {
        for(unsigned short int j = 0; j < M; j++)
        {
            for(unsigned short int k = 0; k < N; k++)
            {
                Serial.print(armJointVec[i][j][k]);
                Serial.print("    ");
            }
            Serial.println(" ");
        }
        Serial.println(" ");
        Serial.print("End of Joint ");
        Serial.print(i + 1);
        Serial.println(" ");
        Serial.println(" ");
    }
}

/**
 * Update robot arm pose matrices based on join configuration
 * 
 * @param joint pass the current vector set of pose transformations (3D)
 * @return Void
 */
void Arm::update(std::vector<std::vector<std::vector<float> > > &joint)
{

    unsigned short int n = joint.size(); // Number of joints
    unsigned short int M = joint[0].size(); // Number of Rows
    unsigned short int N = joint[0][0].size(); // Number of Columns

    // TODO --> Handle exception if M and N do not match

    
    // Peform link matrix multiplication
    for(unsigned short int i = 0; i < n - 1; i++)
    {
        VecMult(joint[i], joint[i + 1], joint[i + 1]);
    }
}

/**
 * Robot homing routine --> Robot arm is upright in the vertical direction
 * 
 * @param armJointVec pass the current vector set of pose transformations (3D)
 * @return Void
 */
void Arm::homing(std::vector<std::vector<std::vector<float> > > &armJointVec)
{
    return;
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
 * @return Link Vector
 */
std::vector<std::vector<float> > Arm::createLink(float rx, float ry, float rz, float tx, float ty, float tz)
{
    // Multi-dimensional pose vector assignment
    std::vector<std::vector<float> > Link = {
        {cos(rz) * cos(ry), cos(rz) * sin(ry) * sin(rx) - sin(rz) * cos(rx), cos(rz) * sin(ry) * cos(rx) + sin(rz) * sin(rx), tx},
        {sin(rz) * cos(ry), sin(rz) * sin(ry) * sin(rx) + cos(rz) * cos(rx), sin(rz) * sin(ry) * cos(rx) - cos(rz) * sin(rx), ty},
        {(float)-1.0 * sin(ry), cos(ry) * sin(rx), cos(ry) * cos(rx), tz},
        {0, 0, 0, 1}
        };

    return Link;
}


// Deconstructor
Arm::~Arm()
{

}