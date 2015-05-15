#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "TimedThread.h"


void* timedThreadHandler(void* thread)
{

    timespec delay;
    timeval current;
    timeval last;
    bool firstLoop = true;

    double dT= 0.005;

    delay.tv_sec = 0;
    delay.tv_nsec = dT*1000000000;

    while ( true )
    {
        gettimeofday(&current, NULL);
        double actualdT = 0;
        if ( firstLoop )
            firstLoop = false;
        else
        {
            double cur = current.tv_sec + (current.tv_usec * 0.000001);
            double las = last.tv_sec + (last.tv_usec * 0.000001);
            actualdT = cur - las;
        }
        last = current;

        ((void (*)(double dT))thread)(actualdT);

        nanosleep(&delay, NULL);
    }
}

pthread_t createTimedThread(void (*routine)(double dT))
{

    pthread_t thread;
    if ( pthread_create(&thread, NULL, timedThreadHandler, (void*)routine) != 0 )
        perror("createTimedThread");

    sched_param rt = {21};
    pthread_setschedparam(thread, SCHED_RR, &rt);

    return thread;
}