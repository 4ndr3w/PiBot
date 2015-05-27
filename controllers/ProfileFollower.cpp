//
// Created by andrew on 5/25/15.
//

#include "ProfileFollower.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "../drivers/MPU6050/SimpleDMP.h"

using namespace std;


ProfileFollowerController::ProfileFollowerController():
        points()
{
    index = 0;
    runProfile = false;
}

void ProfileFollowerController::generate(double target, double vcruise, double maxAccel)
{
    points.clear();
    double t = 0;
    double tToCruise = vcruise/maxAccel;

    for ( t=t; t <= tToCruise; t+= 0.01 )
    {
        ProfilePoint point;

        point.t = t;
        point.vel = maxAccel*t;
        point.pos = (0.5)*maxAccel*(t*t);
        point.acc = maxAccel;

        points.push_back(point);
    }
    double dRamping = (0.5)*maxAccel*(tToCruise*tToCruise);
    double dCruising = target-(dRamping*2);
    double tCruising = dCruising/vcruise;

    for ( double i = 0; i < tCruising; i+= 0.01)
    {
        ProfilePoint point;

        point.t = t;
        point.pos = dRamping+(vcruise*i);
        point.vel = vcruise;
        point.acc = 0;
        t+= 0.01;
        points.push_back(point);
    }

    for ( double i = 0; i < tToCruise; i+= 0.01)
    {
        ProfilePoint point;

        point.t = t;
        point.pos = (dCruising+dRamping)+(vcruise*i)+(0.5)*-maxAccel*(i*i);
        point.vel = vcruise+((-maxAccel)*i);
        point.acc = -maxAccel;
        t += 0.01;
        points.push_back(point);
    }
}

void ProfileFollowerController::start()
{
    index = 0;
    runProfile = true;
}

void ProfileFollowerController::update(Drivetrain *drivetrain)
{
    if ( runProfile )
    {
        double twist = -getAngle()*0.038;

        ProfilePoint p = points.at(index);
        double realVel = p.vel/24.0;
        double realPos = (drivetrain->getEncoder(LEFT_ENC)+drivetrain->getEncoder(RIGHT_ENC))/2;
        double error = p.pos-realPos;
        double speed = (p.vel/23.5) + (error*0.1) + (p.acc*0);
        drivetrain->drive(speed,0,twist);

        index++;
        if ( index >= points.size() )
        {
            index = 0;
            runProfile = false;
        }
    }
    else
        drivetrain->drive(0,0,0);
}

bool ProfileFollowerController::isRunning()
{
    return runProfile;
}