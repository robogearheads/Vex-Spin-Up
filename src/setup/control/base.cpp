#include "setup/control/base.h"
#include "pros/rotation.hpp"

//Drive Motors
pros::Motor RB(12, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES),
            RF(19, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES),
            LB(13, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES),
            LF(20, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
            
//Inertial Sensor
//pros::Imu Inertial(18);

//Encoders
pros::Rotation LeftRotation(18); 
pros::Rotation RightRotation(14); 
pros::Rotation BackRotation(1);

//GPS Sensor
//pros::GPS GPSSensor(5, -0.2032, 0);