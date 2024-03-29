#include "setup/util/odometry.h"

#include "setup/control/base.h"

#define CONVERSION_FACTOR 0.000239982772149 //Centidegrees to inches

//Distance between tracking wheel and center
double leftOffset = 3.75; //3.75 in
double rightOffset = 3.75;
double backOffset = 6.75; //6.75 in

//Initialization
double leftPrev = 0;
double rightPrev = 0;
double backPrev = 0;

double thetaPrev = 0;

//Set start position and angle
double x = 0;
double y = 0;
double heading = 0;
double heading_initial = 0;

void odometry(){
    //Take encoder values
    double leftValueInitial = LeftRotation.get_position();
    double rightValueInitial = RightRotation.get_position();
    double backValueInitial = BackRotation.get_position();

    RightRotation.set_reversed(true);
    BackRotation.set_reversed(true);
    while(true){
        //Take encoder values
        double leftValue = LeftRotation.get_position() - leftValueInitial;
        double rightValue = RightRotation.get_position() - rightValueInitial;
        double backValue = BackRotation.get_position() - backValueInitial;

        //Calculate change - convert centidegrees to inches
        double delta_L = (leftValue - leftPrev)*CONVERSION_FACTOR;
        double delta_R = (rightValue - rightPrev)*CONVERSION_FACTOR;
        double delta_S = (backValue - backPrev)*CONVERSION_FACTOR;

        //Update previous values
        leftPrev = leftValue;
        rightPrev = rightValue;
        backPrev = backValue;

        //Calculate overall distance change for each encoder
        double leftTotal = leftValue*CONVERSION_FACTOR;
        double rightTotal = rightValue*CONVERSION_FACTOR;
        double backTotal = backValue*CONVERSION_FACTOR;

        //Determine absolute heading
        heading = heading_initial + (leftTotal - rightTotal)/(leftOffset + rightOffset);

        //Calculate change in angle and update previous value
        double delta_theta = heading - thetaPrev;
        
        //If there is no angular change, assume straight line motion
        double local_x_change = 0;
        double local_y_change = 0;
        if (delta_theta == 0){ //need to change into a range?
            local_x_change = delta_S;
            local_y_change = (delta_L + delta_R)/2;
        }
        //If not, use arc
        else{
            local_x_change = 2*sin(delta_theta/2)*((delta_S/delta_theta) + backOffset); //should heading or delta_theta be used for the first one?
            local_y_change = 2*sin(delta_theta/2)*((delta_R/delta_theta) + rightOffset);
        }

        //Calculate average orientation - used for rotating local changes to global
        double avgOrientation = thetaPrev + delta_theta/2;
        thetaPrev = heading;

        //Rotate local changes by avg orientation to get absolute changes
        double global_x_change = local_x_change*cos(-avgOrientation) - local_y_change*sin(-avgOrientation); //is avgOrientation negative?
        double global_y_change = local_x_change*sin(-avgOrientation) + local_y_change*cos(-avgOrientation); //is avgOrientation negative?

        //Update position
        x = x + global_x_change;
        y = y + global_y_change;

        pros::lcd::print(0, "x is %f", x);
        pros::lcd::print(1, "y is %f", y);
        pros::lcd::print(2, "heading is %f", heading * 180 / 3.14159265359);

        pros::delay(10);
    }
}

void setPosition(double x_pos, double y_pos, double heading_pos){
    x = x_pos;
    y = y_pos;
    heading_initial = heading_pos;
    heading = 0;

    leftPrev = 0;
    rightPrev = 0;
    backPrev = 0;
    thetaPrev = 0;

    LeftRotation.reset_position();
    RightRotation.reset_position();
    BackRotation.reset_position();
}