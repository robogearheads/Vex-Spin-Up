#include "setup/control/base.h"
#include "pros/motors.h"
#include "pros/rotation.hpp"

//Drive Motors
pros::Motor RB(10, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            RF(11, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            LB(16, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_DEGREES),
            LF(19, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES);
            
//Inertial Sensor
pros::Imu Inertial(18);

//Encoders
pros::Rotation LeftRotation(18); 
pros::Rotation RightRotation(12); 
pros::Rotation BackRotation(8);

//GPS Sensor
//pros::GPS GPSSensor(5, -0.2032, 0);