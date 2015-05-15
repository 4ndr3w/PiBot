#ifndef PICONTROLLER_NETCOMM_H
#define PICONTROLLER_NETCOMM_H
#include "RobotState.h"

void initNetComm();
void lockState();
void unlockState();


RequestedState* getRequestedState();
RobotState* getRobotState();

#endif