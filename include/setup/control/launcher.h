#include "main.h"
#include "pros/imu.hpp"

extern pros::Motor  FW1, FW2;

extern pros::Motor Turret;

extern pros::IMU TurretInertial;

void autoAim();

void controllerAim();