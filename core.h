#ifndef PICONTROLLER_CORE_H
#define PICONTROLLER_CORE_H

#include <wiringPi.h>
#include "timing/TimedThread.h"
#include "drivers/PWM.h"
#include "vision/pixy.h"
#include "drivers/MPU6050/SimpleDMP.h"
#include "robot/Drivetrain.h"

void robotInit(bool initGyro = true, bool initLIDAR = true, bool initPixy = false);

#endif