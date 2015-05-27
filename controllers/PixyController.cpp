#include "PixyController.h"
#include "../vision/pixy.h"
PixyController::PixyController()
{

}

void PixyController::update(Drivetrain* drivetrain)
{
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

        double p = (selectedBlock->x-150)*0.005;
        int area = selectedBlock->height*selectedBlock->width;
        double dist = (4000-area)/10000.0;
        printf("x: %i, size %i, d %2.4f, y %2.4f\n", selectedBlock->x, selectedBlock->height*selectedBlock->width, p, dist);
        drivetrain->drive(dist,0,p);
    }
    else{
        printf("no object found!\n");
        drivetrain->drive(0,0,0);
    }
    pixyUnlockBlocks();
}
