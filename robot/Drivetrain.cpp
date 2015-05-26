#include "Drivetrain.h"
#include "../timing/TimedThread.h"
#include "../network/NetComm.h"
#include "../drivers/PWM.h"
#include <stdio.h>

void drivetrainUpdateThread(double dT);

Drivetrain* Drivetrain::instance = 0;

Drivetrain* Drivetrain::getDrivetrain()
{
    if ( instance == 0 ) {
        instance = new Drivetrain();
        instance->startThread();
    }
    return instance;
}


void enc1ISR()
{
    Drivetrain::getDrivetrain()->encoderTick(0, true);
}

void enc2ISR()
{
    Drivetrain::getDrivetrain()->encoderTick(1, true);
}

void enc3ISR()
{
    Drivetrain::getDrivetrain()->encoderTick(2, true);
}

void enc4ISR()
{
    Drivetrain::getDrivetrain()->encoderTick(3, true);
}


Drivetrain::Drivetrain()
{
    printf("drivetrain init~\n");

    // encoder 1
    pinMode(ENC1_A, INPUT);
    pinMode(ENC1_B, INPUT);
    wiringPiISR(ENC1_A, INT_EDGE_RISING, &enc1ISR);

    // encoder 2
    pinMode(ENC2_A, INPUT);
    pinMode(ENC2_B, INPUT);
    wiringPiISR(ENC2_A, INT_EDGE_RISING, &countEncoder2);

    // encoder 3
    pinMode(ENC3_A, INPUT);
    pinMode(ENC3_B, INPUT);
    wiringPiISR(ENC3_A, INT_EDGE_RISING, &countEncoder3);

    // encoder 4
    pinMode(ENC4_A, INPUT);
    pinMode(ENC4_B, INPUT);
    wiringPiISR(ENC4_A, INT_EDGE_RISING, &countEncoder4);


}


void Drivetrain::startThread()
{
    createTimedThread(drivetrainUpdateThread);
}


void Drivetrain::update(double dT)
{
    lockState();
    RequestedState* state = getRequestedState();
    RobotState* robot = getRobotState();
    //printf("drivetrain update - controller %i\n", state->controller.type);
    Controller::getController(state->controller.type)->update(&state->controller, this);
    unlockState();
}


void Drivetrain::setMotor(DrivetrainMotor motor, double speed)
{
    speed = (speed*250)+400;
    if ( speed > 650 )
        speed = 650;
    else if ( speed < 150 )
        speed = 150;
    setPWM(motor, 0, (int)speed);
}

void Drivetrain::drive(double y, double x, double twist) {
   // printf("drive set %2.4f %2.4f %2.4f\n", y ,x, twist);
    setMotor(LEFT, -y+twist);
    setMotor(RIGHT, -y-twist);

    setMotor(FRONT, x-twist);
    setMotor(BACK, -x-twist);
}

void Drivetrain::encoderTick(DrivetrainEncoder enc, bool forward)
{
    if ( forward )
        encoders[enc]++;
    else
        encoders[enc]--;
}


void drivetrainUpdateThread(double dT)
{
    Drivetrain::getDrivetrain()->update(dT);
}
