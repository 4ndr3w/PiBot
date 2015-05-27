//
// Created by andrew on 5/6/15.
//

#include <assert.h>
#include "PositionController.h"
#include "../drivers/MPU6050/SimpleDMP.h"
#include <stdio.h>

PositionController::PositionController() {
    targetX = 0;
    targetY = 0;
}

void PositionController::setTarget(double x, double y)
{
    targetX = x;
    targetY = y;
}

void PositionController::update(Drivetrain *drivetrain) {
    double twist = -getAngle()*0.038;

    double yDist = targetY-drivetrain->getY();
    double xDist = targetX-drivetrain->getX();
    yDist *= 0.1;
    xDist *= 0.1;

    drivetrain->drive(yDist,xDist,twist);
}