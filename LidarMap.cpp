#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "core.h"
#include "controllers/BrickController.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include "drivers/LIDAR.h"

struct JoystickData
{
    int f;
    int s;
    int t;
};


int main() {
    robotInit();
    Drivetrain *drive = Drivetrain::getDrivetrain(); // start driving thread

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in bindaddr;
    memset(&bindaddr, 0, sizeof(sockaddr_in));
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_port = htons(1337);
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (sockaddr*)&bindaddr, sizeof(sockaddr_in));

    BrickController *brickController = new BrickController();
    drive->setActiveController(brickController);
    while (true) {
        JoystickData data;
        sockaddr src;
        socklen_t src_len = sizeof(src);
        recvfrom(sock, &data, sizeof(JoystickData), 0, &src, &src_len);

        double f = (double)data.f/100.0;
        double s = (double)data.s/100.0;
        double t = -getAngle()*0.03;

        //double t = (double)data.t/100.0;

        double angle = -getAngle();
        double cosA = cos(angle*(M_PI/180));
        double sinA = sin(angle*(M_PI/180));
        double Rf = f*cosA-s*sinA;
        double Rs = f*sinA+s*cosA;

        drive->drive(Rf,Rs,t);

        int out[WIDTH][HEIGHT];
        copyMap((int*)&out);
        sendto(sock, (int*)&out, 50*50*sizeof(int), 0, &src, src_len);
    }
}
