//
// Created by andrew on 5/11/15.
//

#ifndef PICONTROLLER_PIXY_H
#define PICONTROLLER_PIXY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pixy.h>

#define PIXY_MAX_BLOCKS 10


void pixyInit();
void pixyLockBlocks();
void pixyUnlockBlocks();
Block* pixyGetBlocks();

#endif //PICONTROLLER_PIXY_H
