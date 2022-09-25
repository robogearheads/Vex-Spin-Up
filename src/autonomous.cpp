#include "main.h"

#include "setup/util/misc.h"
#include "setup/util/MovementFunctions.h"
#include "setup/util/odometry.h"
#include "setup/util/PurePursuit.h"

void autonomous() {
    
    //Start tasks
    pros::Task Odometry(odometry);
    pros::Task PurePursuit(pure_pursuit_step);
    PurePursuit.suspend();
    pros::Task Movement(movePath);
    Movement.suspend();

    //Call autonomous routines here (use switch case with auton selector)

    std::vector<double> oogaX = {0, -10, -30, -25, -30};
    //oogaX.push_back({10});

    std::vector<double> oogaY = {0, 20, 30, 15, 0};
    //oogaY.push_back({10});
    //{{0, 0}, {-10, 20}, {-30, 30}, {-25, 15}, {-30, 0}};

    //new path
    pathX = oogaX; 
    pathY = oogaY;
    LFindex = 0;

    PurePursuit.resume();
    Movement.resume();
    


}