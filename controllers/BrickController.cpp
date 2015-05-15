#include <assert.h>
#include "BrickController.h"
#include <stdio.h>
#include <unistd.h>


BrickController::BrickController() {

}

void BrickController::update(ControllerParams *input, Drivetrain *drivetrain) {
    assert(input->type == GENERIC_CONTROLLER);

    drivetrain->drive(0,0,0);
}