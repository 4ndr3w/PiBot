#ifndef PICONTROLLER_BRICKCONTROLLER_H
#define PICONTROLLER_BRICKCONTROLLER_H

#include <stdint.h>
#include "RobotController.h"

class BrickController : public Controller {
public:
    BrickController();
    void update(ControllerParams* params, Drivetrain* drivetrain);

};


#endif //PICONTROLLER_BRICKCONTROLLER_H
