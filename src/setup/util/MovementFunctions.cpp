#include "setup/util/MovementFunctions.h"

#include "setup/control/base.h"
#include "setup/util/PurePursuit.h"
#include "setup/util/odometry.h"


double getAngle(double pointX, double pointY) { // returns in degrees
  double currentX = x;
  double currentY = y;
  double angle = atan2(pointX - currentX, pointY - currentY);
  return angle * 180 / M_PI;
}

double getLength(double pointX, double pointY) { // returns inches
  double currentX = x;
  double currentY = y;
  double delta_x = pointX - currentX;
  double delta_y = pointY - currentY;
  return sqrt(delta_x * delta_x + delta_y * delta_y) * 39.3700787402;
}

void movePath() {
  double counter = 0;
  double forwardDistance = 1;

  double fwdError = 100000;
  double fwdIntegral = 0;
  double fwdPrevError = 0;
  double fwdPower = 1;

  double turnError = 1;
  double turnIntegral = 0;
  double turnDerivative = 0;
  double turnPrevError = 0;
  double turnPower = 1;

  double fwd_kP = 11;   // 18
  double fwd_kD = 12.5; // 12.5
  double fwd_kI = 0.07; // 0.1

  double turn_kP = 2.2; // 4
  double turn_kI = 0;   // 0.5
  double turn_kD = 1.2; // 2

  double turnEffect = 0.4;
  double fwdEffect = 0.35;

  while (true) { // add counter back later
    // Calculating distances
    double targetAngle = getAngle(goalPt[0], goalPt[1]);
    forwardDistance = getLength(goalPt[0], goalPt[1]);

    fwdError = forwardDistance;

    double fwdDerivative = fwdError - fwdPrevError;
    fwdPrevError = fwdError;
    fwdIntegral = fwdIntegral + fwdError;
    if (fwdError < 0) {
      fwdIntegral = 0;
    }
    if (fwdError > (0.5 * fwdError)) {
      fwdIntegral = 0;
    }
    fwdPower =
        fwdError * fwd_kP + fwdDerivative * fwd_kD + fwdIntegral * fwd_kI;

    turnError = (targetAngle - heading);
    if (turnError < -180) {
      turnError = turnError + 360;
    } else if (turnError > 180) {
      turnError = turnError - 360;
    }
    double derivative = turnError - turnPrevError;
    turnPrevError = turnError;
    turnIntegral = turnIntegral + turnError;
    if (turnError < 0) {
      turnIntegral = 0;
    }
    if (turnError > 20) {
      turnIntegral = 0;
    }
    turnPower =
        turnError * turn_kP + turnDerivative * turn_kD + turnIntegral * turn_kI;

    double leftPower = fwdEffect * fwdPower + turnEffect * turnPower;
    double rightPower = fwdEffect * fwdPower - turnEffect * turnPower;

    while (leftPower < -200 || leftPower > 200 || rightPower < -200 || rightPower > 200) {
      double scalingFactor = 1;
      scalingFactor = scalingFactor + 0.1;
      leftPower = leftPower / scalingFactor;
      rightPower = rightPower / scalingFactor;
      pros::delay(2);
    }

    LF.move_velocity(leftPower);
    LB.move_velocity(leftPower);
    RF.move_velocity(rightPower);
    RB.move_velocity(rightPower);

    pros::lcd::print(4, "turnPower is %f", turnPower);
    pros::lcd::print(5, "fwdPower is %f", fwdPower);
    pros::lcd::print(6, "leftPower is %f", leftPower);
    pros::lcd::print(7, "rightPower is %f", rightPower);

    pros::delay(15);
  }
}
