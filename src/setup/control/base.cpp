#include "setup/control/base.h"
#include "pros/motors.h"
#include "pros/rotation.hpp"

//Drive Motors
pros::Motor RB(1, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            RF(3, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            LB(17, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES),
            LF(18, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES);
            
//Inertial Sensor
pros::Imu Inertial(16);

//Encoders
pros::Rotation LeftRotation(19); 
pros::Rotation RightRotation(2); 
pros::Rotation BackRotation(20);

//GPS Sensor
//pros::GPS GPSSensor(5, -0.2032, 0);