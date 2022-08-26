/*
Class functions used for servo motor movement

Author: Billal Rahimi
Email: billalrahimi@hotmail.com

Date: 2022-07-29
*/

#include "Servo.hpp"


// Global Initializations
int Servo::pwmChannel = 0;

// Constructor
Servo::Servo()
{
    this->gain = (double)PWM_RES_WIDTH / (double)uS_PWM_WIDTH;
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

void Servo::homeServo()
{
    writePos(180);
}

void Servo::writePos(int pos)
{ 

    if(pos < 0)
    {
        this->pos = sqrt(pow((float) pos, 2));
    }else
    {
        this-> pos = pos;
    }
    
    
    uint32_t DC = calculateDC(this->pos, this->gain);

    ledcWrite(this->currentChannel, DC);
    
}

float Servo::getCurrentPos()
{
    return pos;
}

uint32_t Servo::calculateDC(int pos, double gain)
{
    double transferFunction = (double)pos*(((double)uS_MAX_TIME-(double)uS_MIN_TIME)/(double)ROT_PER_uS) + (double)uS_MIN_TIME;

    return ceil(gain * transferFunction);

}

// Deconstructor
Servo::~Servo()
{
    this->pwmChannel--;
}