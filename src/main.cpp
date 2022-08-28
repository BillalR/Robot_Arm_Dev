// Includes
#include <Arduino.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

// User defined hpp includes
#include "robotArm.hpp"
#include "Servo.hpp"
#include "conversions.hpp"

// Defines
#define BAUD_RATE 115200
#define PWM_FREQ 50
#define BASE_GPIO 25
#define SHOULDER_GPIO 26
#define ELBOW_GPIO 27
#define PI 3.1415926
#define LINK_LENGTH 177.8 // Length in mm

// Class object inititalizer
Arm robot;
Servo Base;
Servo Shoulder;
Servo Elbow;

// Function prototypes
void move_angle(Servo &joint, int rot);
bool move_robot(int x, int y, int z);
double r2d(double theta);
void home_servos();

void setup() {
  
  // Pin mode setups
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BASE_GPIO, OUTPUT);
  pinMode(SHOULDER_GPIO, OUTPUT);
  pinMode(ELBOW_GPIO, OUTPUT);

  //Configure servo objects
  // Freqeuncy setup
  Base.freqSetup(PWM_FREQ);
  Shoulder.freqSetup(PWM_FREQ);
  Elbow.freqSetup(PWM_FREQ);

  // Attach
  Base.attach(BASE_GPIO);
  Shoulder.attach(SHOULDER_GPIO);
  Elbow.attach(ELBOW_GPIO);

  // Initialize Servo Homing
  // Base.homeServo();
  // Shoulder.homeServo();
  // Elbow.homeServo();

  // Home Servos
  home_servos();

  // Initialize Serial Comms
  Serial.begin(BAUD_RATE);

}

void loop() {
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);

  move_robot(150, 150, 250);
  delay(250);
  move_robot(50, 100, 100);
  delay(250);
  move_robot(25, 200, 50);

}

/**
 * Move the servos at a smoother pace -- TEST
 * 
 * @param &joint Servo object reference used to rotate the specific joint -- MUST BE REFERENCE OR ELSE CLASS DOESN'T UPDATE THIS POINTER
 * @param rot rotation in degrees
 * @return void
 */
void move_angle(Servo &joint, int rot)
{
  int current_pos = joint.getCurrentPos();

  if(current_pos < rot)
  {
    for(int i = current_pos; i <= rot; i++)
    {
    joint.writePos(i);
    delay(25);
    }
  }else
  {
    for(int i = current_pos; i >= rot; i--)
    {
    joint.writePos(i);
    delay(25);
    }
  }
  
}

/**
 * Initialize Servos in their home orientaiton
 * 
 * @return void
 */
void home_servos()
{
  move_angle(Base, 0);
  move_angle(Shoulder, 180);
  move_angle(Elbow, 0);
}

/**
 * Servo move routine based on the robot arm servo rotations -- TEST
 * 
 * @param x x-position
 * @param y y-position
 * @param z z-position
 * @return bool Whether the position was executed or if there is a singularity
 */
bool move_robot(int x, int y, int z)
{
  // Calculate the base joint rotation based on the x and y position
  double base_rotation = r2d(atan(y/x));
  Serial.println(base_rotation);

  Serial.println("base before degree conversion");
  Serial.println(atan(y/x));

  // Rotate the base joint
  move_angle(Base, (int)base_rotation);

  // Length of position from base in 2D coordinate frame -- (x,y)
  float length_2D = sqrt(pow(x, 2) + pow(y, 2));

  // Length of position from base in z 2D coordinate frame -- (length_2D, z)
  float length_3D = sqrt(pow(length_2D, 2) + pow(z, 2));

  float phi = atan(z/length_2D);

  // This is a singularity region
  if (length_3D > LINK_LENGTH*2) { return false;}

  float theta = acos((length_3D/2)/(float)LINK_LENGTH);

  float a1 = 180 - r2d(phi - theta);
  float a2 = r2d(phi + theta);

  move_angle(Shoulder, (int)a1);
  move_angle(Elbow, (int)a2);


  return true;
}

/**
 * Servo move routine based on the robot arm servo rotations -- TEST
 * 
 * @param theta angle value in radians
 * @return float angle in degrees
 */
double r2d(double theta)
{
  return theta*180/PI;
}