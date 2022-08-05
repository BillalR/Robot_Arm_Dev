// Includes
#include <Arduino.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

// User defined hpp includes
#include "robotArm.hpp"
#include "ESP32Servo.hpp"

// Defines
#define BAUD_RATE 115200
#define PWM_FREQ 50
#define BASE_GPIO 25
#define SHOULDER_GPIO 26
#define ELBOW_GPIO 27


// Class object inititalizer
Arm robotArm;
Servo Base;
Servo Shoulder;
Servo Elbow;

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
  //ledcSetup(0, 50, 8);
  //ledcAttachPin(25, 0);
  // Attach
  Base.attach(BASE_GPIO);
  Shoulder.attach(SHOULDER_GPIO);
  Elbow.attach(ELBOW_GPIO);

  // Initialize Serial Comms
  Serial.begin(BAUD_RATE);

}

void loop() {
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  //robotArm.printVector();

  // Test Servos
  for(int i = 0; i <= 180; i++)
  {
    Base.writePos(i);
    delay(15);
  }

  for(int i = 180; i>=0; i--)
  {
    Base.writePos(i);
    delay(15);
  }

  
}