#include "setup/control/intake.h"

pros::Motor Intake(0, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

//Moves scissor lift (the way the motor moves may need to change) - in opcontrol, this will run as a short-term task when a button is pressed
void liftDisks(){
    while(Intake.get_position() < 100){ //100 will need to be changed
        Intake.move_velocity(190);
    }
    while(Intake.get_position() > 0){
        Intake.move_velocity(-190);
    }
    Intake.move_velocity(0);
}