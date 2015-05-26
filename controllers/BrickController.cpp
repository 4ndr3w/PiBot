#include <assert.h>
#include "BrickController.h"
#include <stdio.h>
#include <unistd.h>
#include "../drivers/MPU6050/SimpleDMP.h"
BrickController::BrickController() {

}

void BrickController::update(Drivetrain *drivetrain) {
    drivetrain->drive(0,0,0);
}