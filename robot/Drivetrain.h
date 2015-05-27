//
// Created by andrew on 5/8/15.
//

#ifndef PICONTROLLER_DRIVETRAIN_H
#define PICONTROLLER_DRIVETRAIN_H
class Controller;
#include <wiringPi.h>
#include <pthread.h>
#include "../controllers/RobotController.h"
#define ENC1_A 1
#define ENC1_B 0

#define ENC2_A 2
#define ENC2_B 3

#define ENC3_A 5
#define ENC3_B 4

#define ENC4_A 6
#define ENC4_B 7

enum DrivetrainMotor
{
    LEFT = 12,
    RIGHT = 14,
    FRONT = 15,
    BACK = 13
};


enum DriveEncoder
{
    FRONT_ENC = 0,
    RIGHT_ENC = 1,
    LEFT_ENC = 2,
    BACK_ENC = 3
};

class Drivetrain
{
    pthread_t pthread;
    Controller *activeController;
    Drivetrain();
    static Drivetrain* instance;
    int encoders[4] = {0};
    void startThread();
    double xPos;
    double yPos;
public:
    static Drivetrain* getDrivetrain();
    void setMotor(DrivetrainMotor motor, double speed);
    void drive(double y, double x, double twist);
    void encoderTick(int, bool);
    void setActiveController(Controller*);
    double getEncoder(DriveEncoder);
    void update(double dT);

    double getX();
    double getY();
};


#endif //PICONTROLLER_DRIVETRAIN_H
