#include "setup/control/base.h"
#include "pros/motors.h"
#include "pros/rotation.hpp"

//Drive Motors
pros::Motor RB(19, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            RF(10, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            LB(14, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES),
            LF(2, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES);
            
//Inertial Sensor
pros::Imu Inertial(8);

//Encoders
pros::Rotation LeftRotation(12); 
pros::Rotation RightRotation(20); 
pros::Rotation BackRotation(17);

//GPS Sensor
//pros::GPS GPSSensor(5, -0.2032, 0);