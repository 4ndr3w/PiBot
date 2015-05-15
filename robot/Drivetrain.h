//
// Created by andrew on 5/8/15.
//

#ifndef PICONTROLLER_DRIVETRAIN_H
#define PICONTROLLER_DRIVETRAIN_H

#include <pthread.h>

enum DrivetrainMotor
{
    LEFT = 15,
    RIGHT = 12,
    FRONT = 13,
    BACK = 14
};

enum DrivetrainEncoder
{
    LEFT_ENC,
    RIGHT_ENC,
    FRONT_ENC,
    BACK_ENC
};

class Drivetrain
{
    pthread_t pthread;
    Drivetrain();
    static Drivetrain* instance;
    int encoders[4];
public:
    static Drivetrain* getDrivetrain();
    void setMotor(DrivetrainMotor motor, double speed);
    void drive(double y, double x, double twist);
    void encoderTick(DrivetrainEncoder, bool);

    void update(double dT);



};


#endif //PICONTROLLER_DRIVETRAIN_H
