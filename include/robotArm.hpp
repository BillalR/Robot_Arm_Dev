// Includes
#include <Arduino.h>
#include <vector>
#include <math.h>

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


