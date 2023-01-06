#include "main.h"
#include "pros/adi.hpp"
#include "pros/imu.hpp"

extern pros::Motor  FW1, FW2;

extern pros::Motor Turret;

extern pros::IMU TurretInertial;

extern pros::ADIDigitalOut Indexer;

void autoAim();

void controllerAim();

void singleLaunch();

extern pros::ADIDigitalOut Expansion1;
extern pros::ADIDigitalOut Expansion2;