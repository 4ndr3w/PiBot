#include <sys/socket.h>
#include <netinet/in.h>
#include "NetComm.h"
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>

RobotState robotState;
RequestedState requestedState;

pthread_t netThread;
pthread_mutex_t stateLock;

int sock;

void* networkThread(void* n)
{
    while ( true )
    {
        sockaddr ds_target;
        socklen_t len = sizeof(sockaddr);
        RequestedState buf;
        recvfrom(sock, &buf, sizeof(RequestedState), 0, &ds_target, &len);
        printf("packet\n");
        lockState();
        memcpy(&requestedState, &buf, sizeof(RequestedState));
        sendto(sock, &robotState, sizeof(RobotState), 0, &ds_target, len);
        unlockState();
    }
}

void initNetComm()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock!=-1);

    sockaddr_in bindaddr;
    memset(&bindaddr, 0, sizeof(sockaddr_in));
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_port = htons(1337);
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    assert(bind(sock, (sockaddr*)&bindaddr, sizeof(sockaddr_in)) != -1);
    pthread_create(&netThread, NULL, networkThread, NULL);
    pthread_mutex_init(&stateLock, NULL);
}

void lockState()
{
    pthread_mutex_lock(&stateLock);
}

void unlockState()
{
    pthread_mutex_unlock(&stateLock);
}


RequestedState* getRequestedState()
{
    return &requestedState;
}

RobotState* getRobotState()
{
    return &robotState;
}