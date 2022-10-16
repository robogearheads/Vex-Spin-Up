#include "setup/util/PurePursuit.h"

#include "pros/rtos.hpp"
#include "setup/control/base.h"
#include "setup/util/odometry.h"

// Tells if number is positive or negative
int sgn(double num) {
  if (num >= 0) {
    return 1;
  } else {
    return -1;
  }
}

/* b r o k e n
void newPath(std::vector<double> newPathVarX, std::vector<double> newPathVarY) {
    LFindex = 0;
    pathX = newPathVarX;
    pathY = newPathVarY;
}
*/

// pt to pt distance
double pt_to_pt_distance(double pt1[], double pt2[]) {
  double distance = sqrt(pow(pt2[0] - pt1[0], 2) + pow(pt2[1] - pt1[1], 2));
  return distance;
}

// for method to return
// will be removed
/*
struct purePursuitReturn {
  // array declared inside structure
  double goalPt[2];
  double lastFoundIndex;
};
*/

// variables
// double currentPos[2] = {x, y};
double currentHeading = heading;
double lookAheadDis = 0.8;
double linearVel = 100;
//????
bool using_rotation = false;

std::vector<double> pathX;
std::vector<double> pathY;

double goalPt[2];

int LFindex;

double while_counter = 0;
double for_counter = 0;

// double path[][2];

void pure_pursuit_step() {
  while (true) {
    // ranges from 0.7 ft to 1.5 ft
    // Using distance in inches
    double lookAheadDis = 12;

    // extract currentX and currentY
    double currentX = x;
    double currentY = y;

    // used for loop to find intersection
    bool intersectFound = false;
    int startingIndex = LFindex;

    for (int i = startingIndex; i < pathX.size() - 1;
         i++) { // how do you find the length of an array??
      // beginning of line-circle intersection code

      double x1 = pathX.at(i) - currentX;
      double y1 = pathY.at(i) - currentY;
      double x2 = pathX.at(i + 1) - currentX;
      double y2 = pathY.at(i + 1) - currentY;
      double dx = x2 - x1;
      double dy = y2 - y1;
      double dr = sqrt(pow(dx, 2) + pow(dy, 2));
      double D = x1 * y2 - x2 * y1;
      double discriminant = pow(lookAheadDis, 2) * pow(dr, 2) - pow(D, 2);

      // extra
      double dr2 = dr * dr;
      if (discriminant >= 0) {
        double sol_x1 = (D * dy + sgn(dy) * dx * sqrt(discriminant)) / dr2;
        double sol_x2 = (D * dy - sgn(dy) * dx * sqrt(discriminant)) / dr2;
        double sol_y1 = (-D * dx + fabs(dy) * sqrt(discriminant)) / dr2;
        double sol_y2 = (-D * dx - fabs(dy) * sqrt(discriminant)) / dr2;

        // turning to points
        double sol_pt1[2] = {sol_x1 + currentX, sol_y1 + currentY};
        double sol_pt2[2] = {sol_x2 + currentX, sol_y2 + currentY};
        // end of line-cirle intersection code

        double minX = std::min(pathX.at(i), pathX.at(i + 1));
        double minY = std::min(pathY.at(i), pathY.at(i + 1));
        double maxX = std::max(pathX.at(i), pathX.at(i + 1));
        double maxY = std::max(pathY.at(i), pathY.at(i + 1));

        // if one or both of the solutions are in range
        if (((minX <= sol_pt1[0]) && (sol_pt1[0] <= maxX) && (minY <= sol_pt1[1]) && (sol_pt1[1] <= maxY)) ||
            ((minX <= sol_pt2[0]) && (sol_pt2[0] <= maxX) && (minY <= sol_pt2[1]) && (sol_pt2[1] <= maxY))) {

          intersectFound = true;
          // if both intersections are in range, check which is closer
          if (((minX <= sol_pt1[0]) && (sol_pt1[0] <= maxX) && (minY <= sol_pt1[1]) && (sol_pt1[1] <= maxY)) &&
            ((minX <= sol_pt2[0]) && (sol_pt2[0] <= maxX) && (minY <= sol_pt2[1]) && (sol_pt2[1] <= maxY))) {
            // make decision by comparing the distance between intersections and
            // the next point in path
            //pros::lcd::print(2, "2 solutions found");
            double tempPoint[2] = {pathX.at(i + 1), pathY.at(i + 1)};
            if (pt_to_pt_distance(sol_pt1, tempPoint) <
                pt_to_pt_distance(sol_pt2, tempPoint)) {
              // goalPt = sol_pt1
              goalPt[0] = sol_pt1[0];
              goalPt[1] = sol_pt1[1];
            } else {
              // goalPt = sol_pt2
              goalPt[0] = sol_pt2[0];
              goalPt[1] = sol_pt2[1];
            }
          }

          // if not both solutions are in range, take the one thats in range
          else {
            // if solution pt1 is in range, set that as goal point
            //pros::lcd::print(2, "1 solution found");
            if ((minX <= sol_pt1[0]) && (sol_pt1[0] <= maxX) && (minY <= sol_pt1[1]) && (sol_pt1[1] <= maxY)) {
              //use pt 1
              goalPt[0] = sol_pt1[0];
              goalPt[1] = sol_pt1[1];
            } else {
              //use pt 2
              goalPt[0] = sol_pt2[0];
              goalPt[1] = sol_pt2[1];
            }
          }

          // only exit loop if the solution pt found is closer to the next pt in
          // path than the current pos
          double tempPoint[2] = {pathX.at(i + 1), pathY.at(i + 1)};
          double currentPos[2] = {x, y};
          if (pt_to_pt_distance(goalPt, tempPoint) <
              pt_to_pt_distance(currentPos, tempPoint)) {
            // update lastFoundIndex and exit
            LFindex = i;
            pros::lcd::print(1, "Setting LFIndex to i value of: %f", i);

            break;
          } else {
            // in case for some reason the robot cannot find intersection in the
            // next path segment, but we also don't want it to go backward
            LFindex = i + 1;
            pros::lcd::print(2, "Putting LFIndex to i + 1value of: %f", i + 1);

          }
        }

        // if no solutions are in range
        else {
          //pros::lcd::print(2, "no solutions found");
          intersectFound = false;
          // no new intersection found, potentially deviated from the path
          // follow path[lastFoundIndex]
          // goalPt = {path[lastFoundIndex][0], path[lastFoundIndex][1]};
          goalPt[0] = pathX.at(LFindex);
          goalPt[1] = pathY.at(LFindex);
          //pros::lcd::print(0, "x solution is %f", pathX.at(LFindex));
          //pros::lcd::print(1, "y solution is %f", pathY.at(LFindex));
        }
      }
      for_counter ++;
      pros::delay(10);
      //pros::lcd::print(0, "for counter is %f", for_counter);
    }
/*
    // create and return struct
    struct purePursuitReturn toReturn;
    toReturn.goalPt[0] = goalPt[0];
    toReturn.goalPt[1] = goalPt[1];
    toReturn.lastFoundIndex = lastFoundIndex;
*/
    // return toReturn;
    pros::lcd::print(6, "goal pt_x is %f", goalPt[0]);
    pros::lcd::print(7, "goal pt_y is %f", goalPt[1]);
    
    while_counter ++;
    //pros::lcd::print(7, "while counter is %f", while_counter);
    pros::delay(10);
  }
}

struct arr {
  double array[2];
};