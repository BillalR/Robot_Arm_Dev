/*
Class functions used for servo motor movement

Author: Billal Rahimi
Email: billalrahimi@hotmail.com

Date: 2022-07-29
*/

#include "ESP32Servo.hpp"

// Constructor
Servo::Servo()
{
    this->rotConstant = (double)PWM_RES_WIDTH / (double)uS_PWM_WIDTH;
}

void Servo::freqSetup(int pwmFreq)
{
    ledcSetup(PWM_CHAN, pwmFreq, PWM_RES);
}

void Servo::attach(int pin)
{
    this->pin = pin;
    ledcAttachPin(pin, PWM_CHAN);
}

void Servo::writePos(int pos)
{ 

    this-> pos = pos;

    double transferFunction = this->pos*((uS_MAX_TIME-uS_MIN_TIME)/ROT_PER_uS) + uS_MIN_TIME;

    uint32_t DC = ceil(this->rotConstant * transferFunction);
    
    ledcWrite(PWM_CHAN, DC);
    
}
// Deconstructor
Servo::~Servo()
{

}