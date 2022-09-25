#include "main.h"

extern double goalPt[2];

extern int LFindex;

extern std::vector<double> pathX;
extern std::vector<double> pathY;

void newPath(std::vector<double> newPathVarX, std::vector<double> newPathVarY);

void pure_pursuit_step();
