#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "../../timing/TimedThread.h"

MPU6050 mpu;
int packetSize;

bool dmpFinishedInit = false;
float dmpZero = 0;
float dmpLastValue = 0;
float ypr[3];
float yaw = 0;

void DMPupdate(double dT);

float getAngle()
{
  return yaw;
}

void DMPInit()
{
  mpu.initialize();
  assert(mpu.testConnection());

  if ( mpu.dmpInitialize() == 0 )
  {
    mpu.setDMPEnabled(true);
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      printf("DMP Initialization failed\n");
  }
  createTimedThread(DMPupdate);
}

void DMPupdate(double dT)
{
  Quaternion q;           // [w, x, y, z]         quaternion container
  VectorFloat gravity;    // [x, y, z]            gravity vector
  uint8_t fifoBuffer[64];
  // get current FIFO count
  int fifoCount = mpu.getFIFOCount();

  if (fifoCount == 1024) {
      // reset so we can continue cleanly
      mpu.resetFIFO();
      printf("FIFO overflow!\n");

  // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (fifoCount >= 42) {
      // read a packet from FIFO
      mpu.getFIFOBytes(fifoBuffer, packetSize);

      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

      if ( !dmpFinishedInit )
      {
        double delta = ypr[0]-dmpLastValue;

        if ( fabs(delta) < 0.01 )
        {
          dmpFinishedInit = true;
          dmpZero = ypr[0];
        }
        dmpLastValue = ypr[0];
      }
      else
        yaw = ypr[0]-dmpZero;
  }
}
