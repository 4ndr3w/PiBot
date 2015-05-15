/*

#include <pixy.h>
#include <string.h>
#include "../timing/TimedThread.h"
#include "../network/NetComm.h"


void pixyUpdate(double dT)
{
    if ( pixy_blocks_are_new() == 1 )
    {
        Block blocks[10];
        memset(&blocks, 0, sizeof(Block)*10);
        pixy_get_blocks(10, &blocks);
        memcpy()
    }
}

void initPixy()
{
    int err = 0;
    if ( (err=pixy_init()) != 0 )
        pixy_error(err);
    else
        createTimedThread(pixyUpdate);
}*/