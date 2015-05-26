
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pixy.h>
#include "pixy.h"
#include "../timing/TimedThread.h"
#include "../network/NetComm.h"

Block blocks[PIXY_MAX_BLOCKS];

pthread_mutex_t visionMutex;
void pixyUpdate(double dT)
{
    if ( pixy_blocks_are_new() == 1 )
    {
        memset(&blocks[0], 0, sizeof(Block)*PIXY_MAX_BLOCKS);
        pixy_get_blocks(10, &blocks[0]);
    }
}

void pixyLockBlocks()
{
    pthread_mutex_lock(&visionMutex);
}

void pixyUnlockBlocks()
{
    pthread_mutex_unlock(&visionMutex);
}

Block* pixyGetBlocks()
{
    return (Block*)&blocks[0];
}



void pixyInit()
{
    int err = 0;
    pthread_mutex_init(&visionMutex, NULL);
    if ( (err=pixy_init()) != 0 )
        pixy_error(err);
    else
        createTimedThread(pixyUpdate);
}