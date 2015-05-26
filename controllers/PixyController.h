//
// Created by andrew on 5/6/15.
//

#ifndef PICONTROLLER_PIXYCONTROLLER_H
#define PICONTROLLER_PIXYCONTROLLER_H

#include <stdint.h>
#include "RobotController.h"
#include "../robot/Drivetrain.h"
#include <assert.h>

struct PixyControllerParams
{
    int8_t type;
    int8_t signature;
    char data[255];
};

class PixyController : public Controller {
public:
    PixyController();
    void update(ControllerParams* params, Drivetrain* drivetrain);

};


#endif //PICONTROLLER_PIXYCONTROLLER_H
