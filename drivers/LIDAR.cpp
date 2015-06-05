#include "LIDAR.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include "rplidar/rplidar.h"

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif


int map[50][50];


bool run = true;
pthread_t lidar_thread;
pthread_mutex_t lidar_update;
rp::standalone::rplidar::RPlidarDriver * drv;



void* lidar(void* a)
{
    drv = rp::standalone::rplidar::RPlidarDriver::CreateDriver(rp::standalone::rplidar::RPlidarDriver::DRIVER_TYPE_SERIALPORT);

    if (IS_FAIL(drv->connect("/dev/ttyUSB0", 115200))) {
        fprintf(stderr, "Error, cannot bind to the specified serial port\n");
    }

    drv->startScan();
    rplidar_response_measurement_node_t nodes[360*2];
    size_t   count = _countof(nodes);
    u_result     op_result;



    while ( run ) {


        op_result = drv->grabScanData(nodes, count);
        int buf[50][50];
        memset(&buf, 0, WIDTH*HEIGHT*sizeof(int));
        if (IS_OK(op_result)) {
            drv->ascendScanData(nodes, count);
            for (int pos = 0; pos < (int) count; ++pos) {

                double theta = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f;
                double distance = (nodes[pos].distance_q2 / 4.0f)*0.039370; // inches
                if ( distance != 0 )
                {
                    int x = floor(distance*cos(theta*(M_PI/180)));
                    int y = floor(distance*sin(theta*(M_PI/180)));
                    x += (WIDTH/2);
                    y += (HEIGHT/2);
                    if ( (x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT) )
                    {
                        buf[x][y]=1;
                    }

                }

            }


        }
        pthread_mutex_lock(&lidar_update);
        memcpy(&map, &buf, WIDTH*HEIGHT*sizeof(int));
        pthread_mutex_unlock(&lidar_update);
        usleep(100000);

    }

    rp::standalone::rplidar::RPlidarDriver::DisposeDriver(drv);
}

void lidarInit()
{
    run = true;
    pthread_create(&lidar_thread, NULL, lidar, NULL);
    pthread_mutex_init(&lidar_update, NULL);
}

void lidarCleanup()
{
    run = false;
    pthread_join(lidar_thread, NULL);
}

void lidarLock()
{
    pthread_mutex_lock(&lidar_update);
}

void lidarUnlock()
{
    pthread_mutex_unlock(&lidar_update);
}

int getAtPoint(int x, int y)
{
    if ( x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT )
        return map[x][y];
    else
        return 0;
}
void copyMap(int* ptr)
{
    lidarLock();
    memcpy(ptr, &map, WIDTH*HEIGHT*sizeof(int));
    lidarUnlock();
}