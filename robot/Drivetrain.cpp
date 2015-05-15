#include "Drivetrain.h"
#include "../timing/TimedThread.h"
#include "../network/NetComm.h"
#include "../drivers/PWM.h"
#include <stdio.h>

void drivetrainUpdateThread(double dT);

Drivetrain* Drivetrain::instance = 0;

Drivetrain* Drivetrain::getDrivetrain()
{
    if ( instance == 0 )
        instance = new Drivetrain();
    return instance;
}

/*
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
*/

Drivetrain::Drivetrain()
{
    printf("drivetrain init\n");
    createTimedThread(drivetrainUpdateThread);
}


void Drivetrain::update(double dT)
{
    lockState();
    RequestedState* state = getRequestedState();
    RobotState* robot = getRobotState();
    int packetdT = time(NULL)-robot->lastUpdate;
    if ( packetdT > 2 )
        state->controller.type = 0;
    printf("drivetrain update - controller %i\n", state->controller.type);
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
