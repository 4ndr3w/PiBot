#ifndef PICONTROLLER_JOYSTICKDRIVECONTROLLER_H
#define PICONTROLLER_JOYSTICKDRIVECONTROLLER_H

#include <stdint.h>
#include "RobotController.h"

class JoystickDriveController : public Controller {
public:
    JoystickDriveController();
    void update(Drivetrain* drivetrain);

};


#endif //PICONTROLLER_JOYSTICKDRIVECONTROLLER_H
