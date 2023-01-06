#include "main.h"
#include "init.h"

#include "pros/misc.h"
#include "setup/control/base.h"
#include "setup/control/intake.h"
#include "setup/control/launcher.h"

#include "setup/util/MovementFunctions.h"
#include "setup/util/PurePursuit.h"
#include "setup/util/misc.h"
#include "setup/util/odometry.h"


// Driver control code
void opcontrol() {
  // Setting brake modes
  LF.set_brake_mode(MOTOR_BRAKE_COAST);
  LB.set_brake_mode(MOTOR_BRAKE_COAST);
  RF.set_brake_mode(MOTOR_BRAKE_COAST);
  RB.set_brake_mode(MOTOR_BRAKE_COAST);

  // Flywheel motor
  FW1.set_brake_mode(MOTOR_BRAKE_COAST);
  FW2.set_brake_mode(MOTOR_BRAKE_COAST);

  RightRotation.reset_position();
  LeftRotation.reset_position();
  BackRotation.reset_position();

  // Start tasks
  pros::Task Odometry(odometry);
  // pros::Task PurePursuit(pure_pursuit_step);
  bool flywheel_stopped = true;


  while (1) {
    // Drive code
    LF.move(controller.get_analog(ANALOG_LEFT_Y));
    LB.move(controller.get_analog(ANALOG_LEFT_Y));
    RF.move(controller.get_analog(ANALOG_RIGHT_Y));
    RB.move(controller.get_analog(ANALOG_RIGHT_Y));

    //Intake/Shooting
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      Intake.move_velocity(190);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      flywheel_stopped = false;
      Intake.move_velocity(-190);
      FW1.move_velocity(550);
      FW2.move_velocity(550);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
      FW1.move_velocity(0);
      FW2.move_velocity(0);
      flywheel_stopped = true;
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      flywheel_stopped = false;
      FW1.move_velocity(200);
      FW2.move_velocity(200);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      Intake.move_velocity(-190);
    }
    else if(flywheel_stopped == false){
      FW1.move_velocity(200);
      FW2.move_velocity(200);
      Intake.move_velocity(0);
    }
    else{
      Intake.move_velocity(0);
    }

    /*
    //Basic shooting
    if (controller.get_digital((pros::E_CONTROLLER_DIGITAL_R2))) {
      FW1.move_velocity(550);
      FW2.move_velocity(550);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      FW1.move_velocity(200);
      FW2.move_velocity(200);
    } 
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      FW1.move_velocity(0);
      FW2.move_velocity(0);
    }
    */

    //Expansion
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
      Expansion1.set_value(true);
      Expansion2.set_value(true);
    }

    // Constantly print odom values
    pros::lcd::print(0, "x is %f", x);
    pros::lcd::print(1, "y is %f", y);
    pros::lcd::print(2, "heading is %f", heading * 180 / 3.14159265359);
    pros::lcd::print(3, "temp 1 is %f", FW1.get_temperature());
    pros::lcd::print(4, "temp 2 is %f", FW2.get_temperature());
    
    // Next subsystem
    pros::delay(20);
  }
}