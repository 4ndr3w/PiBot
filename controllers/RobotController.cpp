//
// Created by andrew on 5/6/15.
//
#include "BrickController.h"
#include "JoystickDriveController.h"
#include "PositionController.h"
#include "PixyController.h"

Controller* Controller::controllers[NCONTROLLERS] = {0};

Controller* Controller::getController(int i)
{
    if ( i < 0 || i > NCONTROLLERS )
        return controllers[0];
    return controllers[i];
}

void Controller::init()
{
    controllers[GENERIC_CONTROLLER] = new BrickController();
    controllers[POSITION_CONTROLLER] = new PositionController();
    controllers[JOYSTICKDRIVE_CONTROLLER] = new JoystickDriveController();
    controllers[PIXY_CONTROLLER] = new PixyController();
}

Controller::Controller()
{

}
