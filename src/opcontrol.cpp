#include "main.h"

#include "setup/control/base.h"
#include "setup/control/intake.h"
#include "setup/control/launcher.h"

#include "setup/util/misc.h"
#include "setup/util/MovementFunctions.h"
#include "setup/util/odometry.h"
#include "setup/util/PurePursuit.h"

//Driver control code
void opcontrol(){
    //Setting brake modes
	LF.set_brake_mode(MOTOR_BRAKE_COAST);
	LB.set_brake_mode(MOTOR_BRAKE_COAST);
	RF.set_brake_mode(MOTOR_BRAKE_COAST);
	RB.set_brake_mode(MOTOR_BRAKE_COAST);

    //Flywheel motor
    FW1.set_brake_mode(MOTOR_BRAKE_COAST);
    FW2.set_brake_mode(MOTOR_BRAKE_COAST);   

    RightRotation.reset_position();
    LeftRotation.reset_position();
    BackRotation.reset_position();

    //Start tasks
    pros::Task Odometry(odometry);
    //pros::Task PurePursuit(pure_pursuit_step);

    while(1){
        //Drive code
        LF.move(controller.get_analog(ANALOG_LEFT_Y));
        LB.move(controller.get_analog(ANALOG_LEFT_Y));
		RF.move(controller.get_analog(ANALOG_RIGHT_Y));
		RB.move(controller.get_analog(ANALOG_RIGHT_Y));

        //Flywheel Button
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
        {
            FW1.move(115);
            FW2.move(115); 
        }
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
        {
            FW1.move(0);
            FW2.move(0); 
        }

        //Constantly print odom values
        pros::lcd::print(0, "x is %f", x);
        pros::lcd::print(1, "y is %f", y);
        pros::lcd::print(2, "heading is %f", heading*180/3.14159265359);
        pros::lcd::print(3, "temp is %f", FW1.get_temperature());

        //Next subsystem
        pros::delay(20);
    }
}