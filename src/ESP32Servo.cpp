/*
Class functions used for servo motor movement

Author: Billal Rahimi
Email: billalrahimi@hotmail.com

Date: 2022-07-29
*/

#include "ESP32Servo.hpp"


// Global Initializations
int Servo::pwmChannel = 0;

// Constructor
Servo::Servo()
{
    this->rotConstant = (double)PWM_RES_WIDTH / (double)uS_PWM_WIDTH;
    this->pwmChannel++;
    this->currentChannel = this->pwmChannel;

    if(this->pwmChannel > 15)
    {
        delete this;

        Serial.println("Current Object Deleted, Exceeded Max Servos");
    }
}

void Servo::freqSetup(int pwmFreq)
{
    ledcSetup(this->currentChannel, pwmFreq, PWM_RES);
}

void Servo::attach(int pin)
{
    this->pin = pin;
    ledcAttachPin(pin, this->currentChannel);
}

void Servo::writePos(int pos)
{ 

    this-> pos = pos;

    double transferFunction = (double)this->pos*(((double)uS_MAX_TIME-(double)uS_MIN_TIME)/(double)ROT_PER_uS) + (double)uS_MIN_TIME;

    Serial.println(transferFunction);

    uint32_t DC = ceil(this->rotConstant * transferFunction);
    
    Serial.println(DC);

    ledcWrite(this->currentChannel, DC);
    
}
// Deconstructor
Servo::~Servo()
{
    this->pwmChannel--;
}