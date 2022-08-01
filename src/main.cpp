// Includes
#include <Arduino.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

// User defined hpp includes
#include "robotArm.hpp"

// Defines
#define SERIAL 115200

void setup() {
  // Pin mode setups
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize Serial Comms
  Serial.begin(SERIAL);
}

void loop() {
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}