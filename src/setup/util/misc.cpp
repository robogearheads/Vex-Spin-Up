#include "setup/util/misc.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller turret_controller(pros::E_CONTROLLER_PARTNER);

pros::ADIButton color_selector('A');