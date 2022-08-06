// Includes
#include <Arduino.h>
#include <vector>
#include <cmath>

// Defines
// Typical values for MG90S Servos
#define uS_MIN_TIME 500
#define uS_MAX_TIME 2500
#define uS_PWM_WIDTH 20000
#define ROT_PER_uS 180
#define PWM_FREQ 50


// Internal MCU PWM parameters
#define PWM_RES 16
#define PWM_RES_WIDTH 65536
#define PWM_CHAN 0


/**
 * Servo Motor Class
 * 
 * Used to initialize a servo motor
 * for PWM control
 * 
 */
class Servo{
    // Class private params
    private:
        // Variables
        int pos;
        double rotConstant;
        int pin;
    // Class public params
    public:
        // Constructor
        Servo();
        // Deconstructor
        ~Servo();

        // Variables
        
        

        // Function definitions
        void freqSetup(int pwmFreq);
        void attach(int pin);
        void writePos(int pos);
        
};


