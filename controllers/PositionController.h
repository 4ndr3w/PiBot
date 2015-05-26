//
// Created by andrew on 5/6/15.
//

#ifndef PICONTROLLER_POSITIONCONTROLLER_H
#define PICONTROLLER_POSITIONCONTROLLER_H

#include <stdint.h>
#include "RobotController.h"
#include "../robot/Drivetrain.h"

class PositionController : public Controller {
public:
    PositionController();
    void update(Drivetrain* drivetrain);

};


#endif //PICONTROLLER_POSITIONCONTROLLER_H
