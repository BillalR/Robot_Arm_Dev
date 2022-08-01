// Includes
#include <Arduino.h>
#include <vector>
#include <math.h>
// Defines
#define ARM_JOINTS 4
#define POSE_M 4
#define POSE_N 4

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

    // Class public params
    public:
        // Constructor
        Arm();
        // Deconstructor
        ~Arm();

        // Function prototypes
        std::vector<std::vector<float>> createLink(float rx, float ry, float rz, float tx, float ty, float tz);
};


