#include "main.h"

#include "setup/control/base.h"
#include "setup/control/intake.h"
#include "setup/control/launcher.h"
#include "setup/util/odometry.h"

#include "setup/util/misc.h"

#include "setup/util/MovementFunctions.h"

void RollerFront(){
    setPosition(-57, 42, 90*(M_PI/180));
    pros::delay(300);
    Inertial.set_rotation(90);
    pros::delay(300);
    goForwardPID(-2);
    pros::delay(1000); //shoot and do roller
    forwardForDistance(5, 300);
    moveToPoint(-24, 0); //while intaking
    pros::delay(1000); //shoot
    moveToPoint(24, -45);
    //shoot
    /*
    Spin roller
    Move back a tiny bit
    Turn towards disk
    Go forward towards disk and intake the disk
    Shoot 3 disks while being still
    */
}

void RollerSide(){
    /*
    Move forward
    Turn right towards roller
    Go forward a bit until you are touching roller
    Spin the roller
    Move back a lil bit
    Turn towards disk
    Go forward towards disk and intake the disk
    Shoot 3 disks while being still
    */
}

void SinglePlayer(){
    /*
    Spin roller
    Move back a tiny bit
    Turn towards disk
    Go forward towards disk and intake the disk
    Shoot 3 disks while being still
    Turn towards line of 3 disks
    Go forward while intake the 3 disks and stop around the last disk
    Shoot 3 disks while being still
    Continue forward until in line with roller
    Turn toward roller
    Go forward until touching roller
    Spin roller
    Move back as to not touch roller
    */
}

void Skills(){

}