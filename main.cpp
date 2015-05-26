#include <iostream>
#include <unistd.h>
#include "timing/TimedThread.h"
#include "controllers/PositionController.h"
#include "drivers/PWM.h"
#include "vision/pixy.h"
#include "drivers/MPU6050/SimpleDMP.h"


int main() {
    extern pthread_t netThread;
    wiringPiSetup();
    pixyInit();
    //DMPInit();
    printf("init pwm");
    initPWM();
    //printf("done\ninit net\n");
    //initNetComm();
    printf("done\n");
    printf("init drive\n");
    Drivetrain* drive = Drivetrain::getDrivetrain(); // start driving thread

    while (true)
    {
        printf("%i %i\n", drive->getEncoder(2),drive->getEncoder(3));
        usleep(100000);
    }

    printf("done\n");


}