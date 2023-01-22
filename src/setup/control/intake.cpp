#include "setup/control/intake.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

pros::Motor Intake(13, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

pros::Motor Roller(9, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);

