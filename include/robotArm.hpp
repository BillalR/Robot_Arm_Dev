// Includes
#include <Arduino.h>
#include <vector>
#include <math.h>
#include "vectorMath.hpp"
// Defines
#define ARM_JOINTS 4
#define POSE_M 4
#define POSE_N 4
#define LINK_M 4
#define LINK_N 1

/**
 * Robot Arm Class
 * 
 * Used to declare the robot arm links
 * as well as other kinematics features.
 * 
 */
class Arm{
    // Class private params
    private:
        // Variables Definitions

    // Class public params
    public:
        // Constructor
        Arm();
        // Deconstructor
        ~Arm();

        // Variable definitions
        std::vector<std::vector<std::vector<float> > > transVec{ARM_JOINTS, std::vector<std::vector<float> >{POSE_M, std::vector<float>{POSE_N}}};
        std::vector<std::vector<std::vector<float> > > linkVec{ARM_JOINTS, std::vector<std::vector<float> >{LINK_M, std::vector<float>{LINK_N}}};
        // Function prototypes
        std::vector<std::vector<float> > createHT(float tx, float ty, float tz, float rx, float ry, float rz);
        void update();//std::vector<std::vector<std::vector<float> > > &joint);
        void homing(std::vector<std::vector<std::vector<float> > > &armJointVec);
        void printTransVector();
        void printLinkVector();
        void move(float tx, float ty, float tz);
};


