#include <iostream>
#include <unistd.h>
#include "timing/TimedThread.h"
#include "controllers/PositionController.h"
#include "network/NetComm.h"
#include "drivers/PWM.h"
#include "vision/pixy.h"
#include "drivers/MPU6050/SimpleDMP.h"


int main() {
    extern pthread_t netThread;
    pixyInit();
    //DMPInit();
    printf("init pwm");
    initPWM();
    printf("done\ninit net\n");
    initNetComm();
    printf("done\n");
    printf("init drive\n");
    Controller::init();
    Drivetrain::getDrivetrain(); // start driving thread
    printf("done\n");
    pthread_join(netThread, NULL);
}