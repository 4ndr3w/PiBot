#include "core.h"
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include "drivers/LIDAR.h"

void exitHandler(int sig)
{
    Drivetrain *drive = Drivetrain::getDrivetrain();
    drive->setActiveController(NULL);
    drive->drive(0,0,0);
    lidarCleanup();
    printf("\nExiting\n");
    usleep(200000);
    exit(0);
}


void robotInit(bool initGyro, bool initLIDAR, bool initPixy)
{
    wiringPiSetup();
    if ( initPixy )
        pixyInit();
    initPWM();
    if ( initGyro )
        DMPInit();
    if ( initLIDAR )
        lidarInit();
    printf("\nReady to run\n");
    getchar();
    printf("Running\n");
    signal(SIGINT, exitHandler);
}