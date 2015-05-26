#include "PixyController.h"
#include "../vision/pixy.h"
PixyController::PixyController()
{

}

void PixyController::update(ControllerParams* input, Drivetrain* drivetrain)
{
    assert(input->type == PIXY_CONTROLLER);
    PixyControllerParams *params = (PixyControllerParams*)input;

   pixyLockBlocks();
   Block *block = pixyGetBlocks();
   Block *selectedBlock = 0;
   for ( int i = 0; i < PIXY_MAX_BLOCKS; i++ )
   {
        if ( block->signature == 1 )
        {
            selectedBlock = block;
            break;
        }
        block++;
    }

    if ( selectedBlock != 0 ) {

        double p = (selectedBlock->x-150)*0.001;
        printf("x: %i, size %i, d %2.4f\n", selectedBlock->x, selectedBlock->height*selectedBlock->width, p);
        drivetrain->drive(0,p,0);
    }
    else{
        printf("no object found!\n");
        drivetrain->drive(0,0,0);
    }
    pixyUnlockBlocks();
}
