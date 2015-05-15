//
// Created by andrew on 5/6/15.
//

#ifndef PICONTROLLER_POSITIONCONTROLLER_H
#define PICONTROLLER_POSITIONCONTROLLER_H

#include <stdint.h>
#include "RobotController.h"
#include "../robot/Drivetrain.h"

struct PositionControllerParams
{
    int8_t type;
    int8_t x;
    int8_t y;
    char data[254];
};

class PositionController : public Controller {
public:
    PositionController();
    void update(ControllerParams* params, Drivetrain* drivetrain);

};


#endif //PICONTROLLER_POSITIONCONTROLLER_H
