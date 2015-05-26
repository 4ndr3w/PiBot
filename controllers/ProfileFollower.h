//
// Created by andrew on 5/25/15.
//

#ifndef PICONTROLLER_PROFILEFOLLOWER_H
#define PICONTROLLER_PROFILEFOLLOWER_H


class ProfileFollowerController : public Controller {
public:
    ProfileFollowerController();
    void update(Drivetrain* drivetrain);

};

#endif //PICONTROLLER_PROFILEFOLLOWER_H
