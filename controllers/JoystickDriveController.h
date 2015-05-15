#ifndef PICONTROLLER_JOYSTICKDRIVECONTROLLER_H
#define PICONTROLLER_JOYSTICKDRIVECONTROLLER_H

#include <stdint.h>
#include "RobotController.h"

struct JoystickDriveControllerParams
{
    int8_t type;
    int8_t fwd;
    int8_t strafe;
    int8_t twist;
    char data[253];
};

class JoystickDriveController : public Controller {
public:
    JoystickDriveController();
    void update(ControllerParams* params, Drivetrain* drivetrain);

};


#endif //PICONTROLLER_JOYSTICKDRIVECONTROLLER_H
