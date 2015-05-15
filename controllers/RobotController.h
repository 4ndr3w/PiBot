//
// Created by andrew on 5/6/15.
//

#ifndef PICONTROLLER_SOURCE_FILE_H
#define PICONTROLLER_SOURCE_FILE_H
#include <stdint.h>
#include "../robot/Drivetrain.h"

#define NCONTROLLERS 3
#define GENERIC_CONTROLLER 0
#define POSITION_CONTROLLER 1
#define JOYSTICKDRIVE_CONTROLLER 2


struct ControllerParams
{
    int8_t type;
    char data[256]; // padding
};

class Controller
{
    static Controller* controllers[NCONTROLLERS];
public:
    static Controller* getController(int type);
    static void init();
    Controller();
    virtual void update(ControllerParams* params, Drivetrain *drivetrain) = 0;
};

#endif //PICONTROLLER_SOURCE_FILE_H
