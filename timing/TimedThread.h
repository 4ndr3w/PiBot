//
// Created by andrew on 5/6/15.
//

#ifndef PICONTROLLER_TIMEDTHREAD_H
#define PICONTROLLER_TIMEDTHREAD_H

#include <pthread.h>

pthread_t createTimedThread(void (*routine)(double dT));

#endif //PICONTROLLER_TIMEDTHREAD_H
