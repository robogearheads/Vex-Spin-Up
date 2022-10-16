#include "main.h"
#include "setup/control/base.h"

#include "setup/util/misc.h"
#include "setup/util/MovementFunctions.h"
#include "setup/util/odometry.h"
#include "setup/util/PurePursuit.h"

void autonomous() {
    //Start tasks
    pros::Task Odometry(odometry);

    //Call autonomous routines here (use switch case with auton selector)

    std::vector<double> oogaX = {0, 10, 10, 30, 30, 50};
    //oogaX.push_back({10});

    std::vector<double> oogaY = {10, 10, 30, 30, 50, 50};
    //oogaY.push_back({10});
    //{{0, 0}, {-10, 20}, {-30, 30}, {-25, 15}, {-30, 0}};

    //new path
    pathX = oogaX; 
    pathY = oogaY;
    LFindex = 0;
    //goalPt[0] = -36, goalPt[1] = 48;
    pros::delay(1000);
    pros::Task PurePursuit(pure_pursuit_step);
    pros::Task Movement(movePath); 

    while(LFindex < pathX.size()-1){
        pros::delay(10);
        pros::lcd::print(5, "LFindex is %f", LFindex);
    }
    pros::lcd::print(3, "done");
    PurePursuit.suspend();
    Movement.suspend();
    pathX = {};
    pathY = {};
    LFindex = 0;

}