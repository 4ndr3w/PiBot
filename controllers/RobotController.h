//
// Created by andrew on 5/6/15.
//

#ifndef PICONTROLLER_SOURCE_FILE_H
#define PICONTROLLER_SOURCE_FILE_H
#include <stdint.h>
class Drivetrain;
#include "../robot/Drivetrain.h"

class Controller
{
public:
    Controller();
    virtual void update(Drivetrain *drivetrain) = 0;
};

#endif //PICONTROLLER_SOURCE_FILE_H
