#include "main.h"

#include "setup/control/base.h"
#include "setup/control/intake.h"
#include "setup/control/launcher.h"

#include "setup/util/misc.h"
#include "setup/util/MovementFunctions.h"
#include "setup/util/odometry.h"

//Driver control code
void opcontrol(){
    //Setting brake modes
	LF.set_brake_mode(MOTOR_BRAKE_COAST);
	LB.set_brake_mode(MOTOR_BRAKE_COAST);
	RF.set_brake_mode(MOTOR_BRAKE_COAST);
	RB.set_brake_mode(MOTOR_BRAKE_COAST);

    RightRotation.reset_position();
    LeftRotation.reset_position();
    BackRotation.reset_position();

    //Start odometry task
    pros::Task Odometry(odometry);

    while(1){
        //Drive code
        LF.move(controller.get_analog(ANALOG_LEFT_Y));
        LB.move(controller.get_analog(ANALOG_LEFT_Y));
		RF.move(controller.get_analog(ANALOG_RIGHT_Y));
		RB.move(controller.get_analog(ANALOG_RIGHT_Y));

        //Constantly print odom values
        pros::lcd::print(0, "x is %f", x);
        pros::lcd::print(1, "y is %f", y);
        pros::lcd::print(2, "heading is %f", heading*180/3.14159265359);

        //Next subsystem
        pros::delay(20);
    }
}