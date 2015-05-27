#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "core.h"
#include "controllers/PositionController.h"

int main() {
    robotInit();
    Drivetrain *drive = Drivetrain::getDrivetrain(); // start driving thread

    PositionController* posController = new PositionController();
    drive->setActiveController(posController);

    while ( true )
    {
        int xPos = 0;
        int yPos = 0;
        std::cout << "Target X: ";
        std::cin >> xPos;

        std::cout << "Target Y: ";
        std::cin >> yPos;

        posController->setTarget(xPos, yPos);
    }
}