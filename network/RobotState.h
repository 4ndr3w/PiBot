//
// Created by andrew on 5/6/15.
//

#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include "../controllers/RobotController.h"

struct RequestedState
{
    ControllerParams controller;
};

struct RobotState
{
    int x;
    int y;
};

#endif //ROBOTSTATE_H
