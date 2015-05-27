#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "core.h"
#include "controllers/ProfileFollower.h"
using namespace std;
int main() {
    robotInit();
    Drivetrain *drive = Drivetrain::getDrivetrain(); // start driving thread

    ProfileFollowerController* profile = new ProfileFollowerController();
    int distance = 0;
    cout << "Distance: ";
    cin >> distance;

    double velocity;
    cout << "Velocity: ";
    cin >> velocity;

    double acc;
    cout << "Acc: ";
    cin >> acc;
    profile->generate(distance,velocity,acc);
    drive->setActiveController(profile);
    profile->start();
    while ( profile->isRunning() )
        sleep(1);
}