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

    double transferFunction = (double)this->pos*(((double)uS_MAX_TIME-(double)uS_MIN_TIME)/(double)ROT_PER_uS) + (double)uS_MIN_TIME;

    Serial.println(transferFunction);

    uint32_t DC = ceil(this->rotConstant * transferFunction);
    
    Serial.println(DC);

    ledcWrite(PWM_CHAN, DC);
    
}
// Deconstructor
Servo::~Servo()
{

}