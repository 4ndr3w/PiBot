//
// Created by andrew on 6/2/15.
//

#ifndef PIBOT_LIDAR_H
#define PIBOT_LIDAR_H

#define HEIGHT 50
#define WIDTH 50

void lidarInit();
void lidarCleanup();
int getAtPoint(int x, int y);
void copyMap(int* ptr);
void lidarLock();
void lidarUnlock();


#endif //PIBOT_LIDAR_H
