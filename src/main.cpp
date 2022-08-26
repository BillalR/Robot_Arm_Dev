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


// Class object inititalizer
Arm robot;
Servo Base;
Servo Shoulder;
Servo Elbow;

bool INIT = true;
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
  Base.homeServo();
  Shoulder.homeServo();
  Elbow.homeServo();

  // Initialize Serial Comms
  Serial.begin(BAUD_RATE);

}

void loop() {
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  //robotArm.printVector();

  Serial.println("Transformation Vector");
  robot.printTransVector();

  Serial.println("Link Vector");
  robot.printLinkVector();

  //delay(2000);
  //if(INIT)
  //{
    //robot.move(2, 0, 0);
    //INIT = false;
  //}
  //robotArm.update();
  // Test Servos
  //Base.writePos(107);
  //Shoulder.writePos(168);

  delay(2000);
  if(INIT)
  {
  robot.move(0, 2, 0);
  INIT = false;
  }

  // for(unsigned short int i = 0; i < (unsigned short int)robot.linkVec[0][3][0]; i++)
  // {
  //   Base.writePos(i);
  //   delay(25);
  // }

  // for(unsigned short int i = 0; i < (unsigned short int)robot.linkVec[1][3][0]; i++)
  // {
  //   Shoulder.writePos(i);
  //   delay(25);
  // }

  // INIT = false;
  // }
  

  // for(int i = 0; i <= 180; i++)
  // {
  //   Base.writePos(i);
  //   delay(15);
  // }

  // for(int i = 0; i <= 180; i++)
  // {
  //   Shoulder.writePos(i);
  //   delay(15);
  // }

  // for(int i = 180; i>=0; i--)
  // {
  //   Base.writePos(i);
  //   delay(15);
  // }

  // for(int i = 180; i>=0; i--)
  // {
  //   Shoulder.writePos(i);
  //   delay(15);
  // }

  
}