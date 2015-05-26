//
// Created by andrew on 5/25/15.
//

#ifndef PICONTROLLER_PROFILEFOLLOWER_H
#define PICONTROLLER_PROFILEFOLLOWER_H

struct ProfileFollowerParams
{
    int8_t type;
    int8_t x;
    int8_t y;
    char data[254];
};

class ProfileFollowerController : public Controller {
public:
    ProfileFollowerController();
    void update(ControllerParams* params, Drivetrain* drivetrain);

};

#endif //PICONTROLLER_PROFILEFOLLOWER_H
