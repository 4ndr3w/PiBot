#include "core.h"
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>

void exitHandler(int sig)
{
    Drivetrain *drive = Drivetrain::getDrivetrain();
    drive->setActiveController(NULL);
    drive->drive(0,0,0);
    printf("\nExiting\n");
    usleep(200000);
    exit(0);
}


void robotInit()
{
    wiringPiSetup();
    pixyInit();
    initPWM();
    DMPInit();

    printf("\nReady to run\n");
    getchar();
    printf("Running\n");
    signal(SIGINT, exitHandler);
}