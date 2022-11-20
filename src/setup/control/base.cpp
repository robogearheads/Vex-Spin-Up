#include "setup/control/base.h"
#include "pros/motors.h"
#include "pros/rotation.hpp"

//Drive Motors
pros::Motor RB(4, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            RF(8, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            LB(12, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES),
            LF(14, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES);
            
//Inertial Sensor
pros::Imu Inertial(18);

//Encoders
pros::Rotation LeftRotation(2); 
pros::Rotation RightRotation(18); 
pros::Rotation BackRotation(9);

//GPS Sensor
//pros::GPS GPSSensor(5, -0.2032, 0);