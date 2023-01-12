#include "setup/control/launcher.h"

#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "setup/control/base.h"
#include "setup/util/PurePursuit.h"
#include "setup/util/odometry.h"

#include "setup/util/misc.h"

#include "init.h"

// Flywheel motors
pros::Motor FW1(11, MOTOR_GEARSET_6,0, MOTOR_ENCODER_DEGREES),
    FW2(12, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut Expansion1 ('C', false);
pros::ADIDigitalOut Expansion2 ('B', false);