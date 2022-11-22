#include "setup/util/MovementFunctions.h"

#include "setup/control/base.h"
#include "setup/util/PurePursuit.h"
#include "setup/util/odometry.h"

#define CONVERSION_FACTOR 0.000239982772149 //centidegrees to inches


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
  return sqrt(delta_x * delta_x + delta_y * delta_y);
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

  double turnEffect = 4;
  double fwdEffect = 0.35;

  while (true) { // add counter back later
    // Calculating distances
    //pros::lcd::print(5, "moving");
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

    while (leftPower < -600 || leftPower > 600 || rightPower < -600 || rightPower > 600) {
      double scalingFactor = 1;
      scalingFactor = scalingFactor + 0.1;
      leftPower = leftPower / scalingFactor;
      rightPower = rightPower / scalingFactor;
      pros::delay(2);
    }

    LF.move_velocity(leftPower/2);
    LB.move_velocity(leftPower/2);
    RF.move_velocity(rightPower/2);
    RB.move_velocity(rightPower/2);

    //pros::lcd::print(4, "turnPower is %f", turnPower);
    //pros::lcd::print(5, "fwdPower is %f", fwdPower);
    //pros::lcd::print(6, "leftPower is %f", leftPower);

    pros::delay(15);
  }
}

//Other stuff
//Function to go forward at a certain speed
void forwardVelocity(double velocity){
  LF.move_velocity(velocity);
  LB.move_velocity(velocity);
  RF.move_velocity(velocity);
  RB.move_velocity(velocity);
}

//Stops
void stop1(){
  LF.move_velocity(0);
  LB.move_velocity(0);
  RF.move_velocity(0);
  RB.move_velocity(0);
}


void turnPID(double targetTheta) {
    pros::lcd::print(1, "running turn PID");
		double current_angle = heading;
		double error = 2;
		double integral = 0;
		double derivative = 0;
		double prevError = 0;
		double power = 1;
    double counter = 0;

		double kP = 1.3; //4
		double kI = 0; //0.5
		double kD = 0.8; //2

		while((error < -0.07 || error > 0.07) && counter < 400){ //Was -0.2
			error = (targetTheta - Inertial.get_heading());
      pros::lcd::print(0, "error is %.3f", error);
      if(error < -180){
        error = error + 360;
      }
      else if(error > 180){
        error = error - 360;
      }
			double derivative = error - prevError;
			prevError = error;
			integral = integral + error;
			if (error < 0){
				integral = 0;
			}
			if (error > 20){
				integral = 0;
			}
			power = error*kP + derivative*kD + integral*kI;
			LF.move_velocity(power);
			LB.move_velocity(power);
			RF.move_velocity(-power);
			RB.move_velocity(-power);
      counter ++;
			pros::delay(5);
		}
		LF.move_velocity(0);
		LB.move_velocity(0);
		RF.move_velocity(0);
		RB.move_velocity(0);
    pros::lcd::print(6, "exiting loop");
}

void preciseTurnPID(double targetTheta) {
		double error = 1;
		double integral = 0;
		double derivative = 0;
		double prevError = 0;
		double power = 1;
    double counter = 0;

		double kP = 1.9; //4
		double kI = 0; //0.5
		double kD = 1.2; //2

		while((error < -0.01 || error > 0.01) && counter < 400){ //Was -0.003
			error = (targetTheta - (heading* 180 / 3.14159265359));
      pros::lcd::print(0, "error is %.3f", error);
      if(error < -180){
        error = error + 360;
      }
      else if(error > 180){
        error = error - 360;
      }
			double derivative = error - prevError;
			prevError = error;
			integral = integral + error;
			if (error < 0){
				integral = 0;
			}
			if (error > 20){
				integral = 0;
			}
			power = error*kP + derivative*kD + integral*kI;
			LF.move_velocity(power);
			LB.move_velocity(power);
			RF.move_velocity(-power);
			RB.move_velocity(-power);
      counter ++;
			pros::delay(5);
		}
		LF.move_velocity(0);
		LB.move_velocity(0);
		RF.move_velocity(0);
		RB.move_velocity(0);
    pros::lcd::print(6, "exiting loop");
}

void goForwardPID(double distance){
  double error = 1;
	double integral = 0;
	double prevError = 0;
	double power = 1;
  double counter = 0;
	double kP = 11; //18
	double kD = 12.5; //12.5
	double kI = 0.07; //0.1

  //current motor values
  double current = LeftRotation.get_position() * CONVERSION_FACTOR;

	while ((error > 0.3 || error < -0.3) && counter < 200){

    //forward distance
    double DistanceTraveled = LeftRotation.get_position()*CONVERSION_FACTOR - current;
		error = distance - DistanceTraveled;
		pros::lcd::print(4, "error is %.3f", error);
		double derivative = error - prevError;
		prevError = error;
		integral = integral + error;
		if (error < 0){
			integral = 0;
		}
		if (error > (0.5*distance)){
			integral = 0;
		}
		power = error*kP + derivative*kD + integral*kI;
	  forwardVelocity(power);
    counter ++;
		pros::delay(15);
	}
  stop1();
}

void moveToPoint(double targetX, double targetY){
  double targetAngle = getAngle (targetX, targetY);
  double forwardDistance = getLength(targetX, targetY);

  preciseTurnPID(targetAngle);
  pros::delay(100);
  goForwardPID(forwardDistance);
}

void preciseBackToPoint(double targetX, double targetY){
  double targetAngle = getAngle (targetX, targetY);
  double forwardDistance = getLength(targetX, targetY);

  preciseTurnPID(targetAngle + 180);
  pros::delay(100);
  goForwardPID(-forwardDistance);
}

void backToPoint(double targetX, double targetY){
  double targetAngle = getAngle (targetX, targetY);
  double forwardDistance = getLength(targetX, targetY);

  turnPID(targetAngle + 180);
  pros::delay(100);
  goForwardPID(-forwardDistance);
}

void fastGoForwardPID(double distance){
  double error = 1;
	double integral = 0;
	double prevError = 0;
	double power = 1;
  double counter = 0;
	double kP = 25; //24
	double kD = 12.5; //12.5
	double kI = 0.07; //0.1

  //current motor values
  double LFcurrent = LF.get_position() * CONVERSION_FACTOR;
  double LBcurrent = LB.get_position() * CONVERSION_FACTOR;
  double RFcurrent = RF.get_position() * CONVERSION_FACTOR;
  double RBcurrent = RB.get_position() * CONVERSION_FACTOR;

	while ((error > 0.08 || error < -0.08) && counter < 300){ //0.1
    //forward distances (motors separate)
    double LFdistance = LF.get_position()*CONVERSION_FACTOR - LFcurrent;
    double LBdistance = LB.get_position()*CONVERSION_FACTOR - LBcurrent;
    double RFdistance = RF.get_position()*CONVERSION_FACTOR - RFcurrent;
    double RBdistance = RB.get_position()*CONVERSION_FACTOR - RBcurrent;

    double avgDistanceTraveled = (LFdistance + LBdistance + RFdistance + RBdistance)/4;

		error = distance - avgDistanceTraveled;
		pros::lcd::print(4, "error is %.3f", error);
		double derivative = error - prevError;
		prevError = error;
		integral = integral + error;
		if (error < 0){
			integral = 0;
		}
		if (error > (0.5*distance)){
			integral = 0;
		}
		power = error*kP + derivative*kD + integral*kI;
	  forwardVelocity(power);
    counter ++;
		pros::delay(15);
	}
  stop1();
}

void DriverBalancePID(){
  double error = 0;
	double derivative = 0;
	double prevError = 0;
	double power = 1;

	double kP = 3.5;
	double kD = 3;

  //Climbing PD
  while(true){
    error = Inertial.get_pitch();
    double derivative = error - prevError;
		prevError = error;
		power = error*kP + derivative*kD;
    forwardVelocity(power);
		pros::delay(15);
	}
}

void driverMovement(){
  //Drive Code
  LF.move(controller.get_analog(ANALOG_LEFT_Y));
  LB.move(controller.get_analog(ANALOG_LEFT_Y));
  RF.move(controller.get_analog(ANALOG_RIGHT_Y));
  RB.move(controller.get_analog(ANALOG_RIGHT_Y));
}

void forwardForDistance(double amount, double speed){
  double current = RightRotation.get_position() * CONVERSION_FACTOR;

  double DistanceTraveled = 1;
  double counter = 0;

  while(DistanceTraveled < amount && counter < 350){

    DistanceTraveled = RightRotation.get_position()*CONVERSION_FACTOR - current;
    forwardVelocity(speed);

    counter ++;

    pros::delay(20);
  }
  stop1();
}
