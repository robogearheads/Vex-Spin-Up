#include "main.h"

#include "setup/control/base.h"
#include "setup/control/intake.h"
#include "setup/control/launcher.h"
#include "setup/util/odometry.h"

#include "setup/util/misc.h"

#include "setup/util/MovementFunctions.h"

#include "init.h"

void RedRollerFront(){
    //Start flywheels
    FW1.move_velocity(599);
    FW2.move_velocity(599);

    //Roller
    goForwardPID(-1);
    Roller.move_velocity(90);
    pros::delay(250);
    Roller.move_velocity(0);
    goForwardPID(1);

    //Shoot first two
    turnPID(-5);
    Intake.move_velocity(0);
    pros::delay(100);
    Intake.move_velocity(-190);
    pros::delay(2500);
    Intake.move_velocity(0);

    //Move to and intake next disks
    FW1.move_velocity(350);
    FW2.move_velocity(350);
    goForwardPID(2);
    turnPID(48);
    Intake.move_velocity(199);
    goForwardPID(29);
    forwardForDistance(20, 100);

    //Aim and Shoot next disks
    FW1.move_velocity(520);
    FW2.move_velocity(520);
    turnPID(-42);
    pros::delay(500);
    Intake.move_velocity(-180);
    pros::delay(5000);

    //Stop all motors
    Intake.move_velocity(0);
    FW1.move_velocity(0);
    FW2.move_velocity(0);    
}

void RedRollerSide(){
    //Start flywheels
    FW1.move_velocity(590);
    FW2.move_velocity(590);

    //Rollers
    goForwardPID(-20);
    turnPID(0);
    goForwardPID(-3);
    Roller.move_velocity(90);
    pros::delay(200);
    Roller.move_velocity(0);
    goForwardPID(3);

    //Shoot
    turnPID(10);
    Intake.move_velocity(-120);
    pros::delay(3000);
    Intake.move_velocity(0);
    FW1.move_velocity(300);
    FW2.move_velocity(300);

    //Intake next disks
    Intake.move_velocity(190);
    turnPID(-47);
    //goForwardPID(60);
    forwardForDistance(60, 275);

    //Aim and Shoot next disks
    FW1.move_velocity(470);
    FW2.move_velocity(470);
    turnPID(45);
    pros::delay(500);
    Intake.move_velocity(-199);
    pros::delay(5000);

    //Stop all motors
    Intake.move_velocity(0);
    FW1.move_velocity(0);
    FW2.move_velocity(0);
}

void RedSinglePlayer(){
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

void BlueRollerFront(){
    /*
    Spin roller
    Move back a tiny bit
    Turn towards disk
    Go forward towards disk and intake the disk
    Shoot 3 disks while being still
    */
}

void BlueRollerSide(){
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

void BlueSinglePlayer(){
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
    //Start flywheels
    FW1.move_velocity(450);
    FW2.move_velocity(450);

    //Roller
    goForwardPID(-1);
    Roller.move_velocity(90);
    pros::delay(550);
    Roller.move_velocity(0);
    goForwardPID(1);

    //Shoot first two
    turnPID(-5);
    goForwardPID(24);
    Intake.move_velocity(0);
    Intake.move_velocity(-90);
    pros::delay(2500);
    Intake.move_velocity(0);
    goForwardPID(-24);

    //Move to and intake next disks
    FW1.move_velocity(350);
    FW2.move_velocity(350);
    goForwardPID(2);
    turnPID(50);
    Intake.move_velocity(190);
    goForwardPID(29);
    forwardForDistance(20, 100);

    //Aim and Shoot next disks
    FW1.move_velocity(500);
    FW2.move_velocity(500);
    turnPID(-41);
    pros::delay(100);
    Intake.move_velocity(-130);
    pros::delay(5000);

    //Stop all motors
    Intake.move_velocity(0);
    FW1.move_velocity(0);
    FW2.move_velocity(0);    

    turnPID(50);
    goForwardPID(-43);
    turnPID(90);
    goForwardPID(30);
    Roller.move_velocity(90);
    pros::delay(500);
    Roller.move_velocity(0);
    goForwardPID(18);
    turnPID(45);

    pros::delay(1000);

    Expansion1.set_value(true);
    Expansion2.set_value(true);

}