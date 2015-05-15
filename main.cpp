#include <iostream>
#include <unistd.h>
#include "timing/TimedThread.h"
#include "controllers/PositionController.h"
#include "network/NetComm.h"
#include "drivers/PWM.h"


int main() {
    extern pthread_t netThread;
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