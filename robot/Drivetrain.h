//
// Created by andrew on 5/8/15.
//

#ifndef PICONTROLLER_DRIVETRAIN_H
#define PICONTROLLER_DRIVETRAIN_H
class Controller;
#include <wiringPi.h>
#include <pthread.h>
#include "../controllers/RobotController.h"
#define ENC1_A 0
#define ENC1_B 1

#define ENC2_A 2
#define ENC2_B 3

#define ENC3_A 4
#define ENC3_B 5

#define ENC4_A 6
#define ENC4_B 7

enum DrivetrainMotor
{
    LEFT = 15,
    RIGHT = 12,
    FRONT = 13,
    BACK = 14
};

class Drivetrain
{
    pthread_t pthread;
    Controller *activeController;
    Drivetrain();
    static Drivetrain* instance;
    int encoders[4] = {0};
    void startThread();
public:
    static Drivetrain* getDrivetrain();
    void setMotor(DrivetrainMotor motor, double speed);
    void drive(double y, double x, double twist);
    void encoderTick(int, bool);
    int getEncoder(int);
    void update(double dT);



};


#endif //PICONTROLLER_DRIVETRAIN_H
