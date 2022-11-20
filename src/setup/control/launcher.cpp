#include "setup/control/launcher.h"

#include "pros/misc.h"
#include "pros/motors.h"
#include "setup/control/base.h"
#include "setup/util/PurePursuit.h"
#include "setup/util/odometry.h"

#include "setup/util/misc.h"

// Flywheel motors
pros::Motor FW1(5, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES),
    FW2(7, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_DEGREES);

// Turret Motor
pros::Motor Turret(1, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

// Inertial Sensor
pros::Imu TurretInertial(3);


double launchGetAngle(double pointX, double pointY) { // returns in degrees
  double currentX = x;
  double currentY = y;
  double angle = atan2(pointX - currentX, pointY - currentY);
  return angle * 180 / M_PI;
}

double launchGetLength(double pointX, double pointY) { // returns inches
  double currentX = x;
  double currentY = y;
  double delta_x = pointX - currentX;
  double delta_y = pointY - currentY;
  return sqrt(delta_x * delta_x + delta_y * delta_y);
}


void autoAim() {
  double error = 2;
  double integral = 0;
  double derivative = 0;
  double prevError = 0;
  double power = 1;
  double counter = 0;

  double kP = 2.5; // 4
  double kI = 0;   // 0.5
  double kD = 0.8; // 2

  double scale = 2;

  while (true) {
    double targetTheta = launchGetAngle(48, 48); // insert goql pt
    double distance = launchGetLength(48, 48);   // insert goal pt

    error = (targetTheta - TurretInertial.get_heading());
    if (error < -180) {
      error = error + 360;
    } else if (error > 180) {
      error = error - 360;
    }
    double derivative = error - prevError;
    prevError = error;
    integral = integral + error;
    if (error < 0) {
      integral = 0;
    }
    if (error > 20) {
      integral = 0;
    }
    power = error * kP + derivative * kD + integral * kI;
    Turret.move_velocity(power);

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        FW1.move_velocity(380 + distance * scale);
        FW2.move_velocity(380 + distance * scale);
    }
    else if(controller.get_digital (pros::E_CONTROLLER_DIGITAL_L2)){
        FW1.move_velocity(300);
        FW2.move_velocity(300);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
        FW1.move_velocity(0);
        FW2.move_velocity(0);
    }
    counter++;
    pros::delay(15);
  }
}

void controllerAim(){
  while(1){
    turret_controller.print(0, 0, "Rotation: %.1f", Turret.get_position()*84/204);
    pros::delay(500);
  }
  
}