/*
Class functions used for robot arm manipulations.

Author: Billal Rahimi
Email: billalrahimi@hotmail.com

Date: 2022-07-29
*/

#include "robotArm.hpp"
#include "conversions.hpp"

// Constructor
Arm::Arm()
{
    // TODO --> Create an initializer that reads current servo values
    // TODO --> Better name for transVec, as it stores the HT vectors
    // Assign link initial values

    // Assign transformation matrices initial values based on servo homing position
    transVec[0] = {createHT(0, 0, 0, 0, 0, 180)};
    VecMult(transVec[0], createHT(0, 0, inches(7), 0, 0, 180), transVec[1]);

    // Assign Link physical length and rotation parameters
    linkVec[0] = {{0}, {0}, {0}, {1}};
    linkVec[1] = {{0}, {inches(7)}, {0}, {1}};
    linkVec[2] = {{0}, {inches(7)}, {0}, {1}};
    linkVec[3] = {{0}, {inches(7)}, {0}, {1}};

}

/**
 * Servo move routine based on the robot arm link set pose
 * 
 * @param transVec pass the current vector set of pose transformations
 * @return Void
 */

void Arm::move(float tx, float ty, float tz)
{
    // Update 
    // Assign transformation matrices initial values based on servo homing position
    transVec[0] = {createHT(0, 0, 0, 0, 0, 180)};
    VecMult(transVec[0], createHT(inches(tx), inches(ty), inches(tz), 0, 0, 180), transVec[1]);

    Serial.println("added values");
    update();

    return;
}

void Arm::printTransVector()
{
    
    unsigned short int n = transVec.size();
    unsigned short int M = transVec[0].size();
    unsigned short int N = transVec[0][0].size();

    for(unsigned short int i = 0; i < n; i++)
    {
        for(unsigned short int j = 0; j < M; j++)
        {
            for(unsigned short int k = 0; k < N; k++)
            {
                Serial.print(transVec[i][j][k]);
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

void Arm::printLinkVector()
{
    
    unsigned short int n = linkVec.size();
    unsigned short int M = linkVec[0].size();
    unsigned short int N = linkVec[0][0].size();

    for(unsigned short int i = 0; i < n; i++)
    {
        for(unsigned short int j = 0; j < M; j++)
        {
            for(unsigned short int k = 0; k < N; k++)
            {
                Serial.print(linkVec[i][j][k]);
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
void Arm::update()//std::vector<std::vector<std::vector<float> > > &joint)
{

    unsigned short int nTrans = transVec.size(); // Number of transformations
    unsigned short int MTrans = transVec[0].size(); // Number of Transformation Rows

    unsigned short int nLink = linkVec.size(); // Number of links
    unsigned short int MLink = linkVec[0].size(); // Number of Link Rows

    // Peform transformation vector multiplication
    for(unsigned short int i = 0; i < nTrans - 1; i++)
    {
        // Update the transformation matrices
        VecMult(transVec[i], transVec[i + 1], transVec[i + 1]);
    }

    // Peform transformation multiplication on physical link vectors
    for(unsigned short int i = 0; i < nTrans; i++)
    {
        // Update the physical links based on transformation calcs above
        VecMult(linkVec[i], transVec[i], linkVec[i]);
    }
}

/**
 * Robot homing routine --> Robot arm is upright in the vertical direction
 * 
 * @param transVec pass the current vector set of pose transformations (3D)
 * @return Void
 */
void Arm::homing(std::vector<std::vector<std::vector<float> > > &transVec)
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
std::vector<std::vector<float> > Arm::createHT(float tx, float ty, float tz, float rx, float ry, float rz)
{
    // Multi-dimensional pose vector assignment
    std::vector<std::vector<float> > T = {
        {cos(rz) * cos(ry), cos(rz) * sin(ry) * sin(rx) - sin(rz) * cos(rx), cos(rz) * sin(ry) * cos(rx) + sin(rz) * sin(rx), tx},
        {sin(rz) * cos(ry), sin(rz) * sin(ry) * sin(rx) + cos(rz) * cos(rx), sin(rz) * sin(ry) * cos(rx) - cos(rz) * sin(rx), ty},
        {(float)0 * sin(ry), cos(ry) * sin(rx), cos(ry) * cos(rx), tz},
        {0, 0, 0, 1}
        };

    return T;
}

// Deconstructor
Arm::~Arm()
{

}