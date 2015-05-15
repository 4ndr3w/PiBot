//
// Created by andrew on 5/6/15.
//

#include <assert.h>
#include "PositionController.h"


PositionController::PositionController() {

}

void PositionController::update(ControllerParams *input, Drivetrain *drivetrain) {
    assert(input->type == POSITION_CONTROLLER);
    PositionControllerParams *params = (PositionControllerParams*)input;
}