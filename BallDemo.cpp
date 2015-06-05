#include <stdio.h>
#include <unistd.h>
#include "core.h"
#include "controllers/PixyController.h"

int main() {
    robotInit(false, true, false);
    Drivetrain *drive = Drivetrain::getDrivetrain(); // start driving thread

    PixyController* pixy = new PixyController();
    drive->setActiveController(pixy);

    while ( true )
        sleep(1);
}