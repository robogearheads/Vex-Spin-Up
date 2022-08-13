#include "setup/control/launcher.h"

//Flywheel motors
pros::Motor FW1(17, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES),
            FW2(16, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES);