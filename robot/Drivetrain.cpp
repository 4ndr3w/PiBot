#include "Drivetrain.h"
#include "../timing/TimedThread.h"
#include "../drivers/PWM.h"
#include "../drivers/MPU6050/SimpleDMP.h"
#include <math.h>
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
    if ( digitalRead(ENC1_B) )
        Drivetrain::getDrivetrain()->encoderTick(0, true);
    else
        Drivetrain::getDrivetrain()->encoderTick(0, false);
}

void enc2ISR()
{
    if ( digitalRead(ENC2_B) )
        Drivetrain::getDrivetrain()->encoderTick(1, true);
    else
        Drivetrain::getDrivetrain()->encoderTick(1, false);
}

void enc3ISR()
{
    if ( digitalRead(ENC3_B) )
        Drivetrain::getDrivetrain()->encoderTick(2, true);
    else
        Drivetrain::getDrivetrain()->encoderTick(2, false);
}

void enc4ISR()
{
    if ( digitalRead(ENC4_B) )
        Drivetrain::getDrivetrain()->encoderTick(3, true);
    else
        Drivetrain::getDrivetrain()->encoderTick(3, false);

}


Drivetrain::Drivetrain()
{
    // encoder 1
    pinMode(ENC1_A, INPUT);
    pinMode(ENC1_B, INPUT);
    wiringPiISR(ENC1_A, INT_EDGE_RISING, &enc1ISR);

    // encoder 2
    pinMode(ENC2_A, INPUT);
    pinMode(ENC2_B, INPUT);
    wiringPiISR(ENC2_A, INT_EDGE_RISING, &enc2ISR);

    // encoder 3
    pinMode(ENC3_A, INPUT);
    pinMode(ENC3_B, INPUT);
    wiringPiISR(ENC3_A, INT_EDGE_RISING, &enc3ISR);

    // encoder 4
    pinMode(ENC4_A, INPUT);
    pinMode(ENC4_B, INPUT);
    wiringPiISR(ENC4_A, INT_EDGE_RISING, &enc4ISR);

    activeController = NULL;
}


void Drivetrain::startThread()
{
    createTimedThread(drivetrainUpdateThread);
}

void Drivetrain::setActiveController(Controller *controller)
{
    activeController = controller;
}


void Drivetrain::update(double dT)
{
    static double lastEncoder[4] = {0};

    double yDiff = ((getEncoder(LEFT_ENC)-lastEncoder[LEFT_ENC])+(getEncoder(RIGHT_ENC)-lastEncoder[RIGHT_ENC]))/2;
    double xDiff = ((getEncoder(FRONT_ENC)-lastEncoder[FRONT_ENC])+(getEncoder(BACK_ENC)-lastEncoder[BACK_ENC]))/2;
    double sinAngle = sin(getAngle()*(M_PI/180));
    double cosAngle = cos(getAngle()*(M_PI/180));

    yPos += (yDiff*cosAngle)+(xDiff*sinAngle);
    xPos += (yDiff*sinAngle)+(xDiff*cosAngle);

    /*printf("diff(%2.4f, %2.4f) SinCos(%2.2f,%2.2f) pos(%2.4f,%2.4f)\n",
           xDiff, yDiff,
           sinAngle, cosAngle,
           xPos, yPos);*/
    for ( int i = 0; i < 4; i++ )
    {
        lastEncoder[i] = getEncoder((DriveEncoder) i);
    }
    if ( activeController != 0 )
        activeController->update(this);
    else
        drive(0,0,0);
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
    setMotor(LEFT, y+twist);
    setMotor(RIGHT, -y+twist);

    setMotor(FRONT, -x-twist);
    setMotor(BACK, -x+twist);
}

void Drivetrain::encoderTick(int enc, bool forward)
{
    if ( forward )
        encoders[enc]++;
    else
        encoders[enc]--;
}

double Drivetrain::getEncoder(DriveEncoder enc)
{
    double dist = encoders[enc]/280.0;
    return dist*(M_PI*4);
}

double Drivetrain::getY()
{
    return yPos;
}

double Drivetrain::getX()
{
    return xPos;
}

void drivetrainUpdateThread(double dT)
{
    Drivetrain::getDrivetrain()->update(dT);
}
