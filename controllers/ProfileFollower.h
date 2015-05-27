//
// Created by andrew on 5/25/15.
//

#ifndef PICONTROLLER_PROFILEFOLLOWER_H
#define PICONTROLLER_PROFILEFOLLOWER_H
#include <vector>
#include "RobotController.h"

struct ProfilePoint {
    double t;
    double pos;
    double vel;
    double acc;
};

class ProfileFollowerController : public Controller {
    std::vector<ProfilePoint> points;
    int index;
    bool runProfile;
public:
    ProfileFollowerController();
    void generate(double target, double vcruise, double maxAccel);
    void start();
    bool isRunning();
    void update(Drivetrain *drivetrain);
};

#endif //PICONTROLLER_PROFILEFOLLOWER_H
