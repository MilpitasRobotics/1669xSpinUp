#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"

void move_roller(){
while (master.get_digital(DIGITAL_L1)){
    conveyorRoller.move_velocity(50); // need to figure out which speed is best for this
}
conveyorRoller.move_velocity(0);
}

void auton_roller(){
    conveyorRoller.move_relative(50, 50); // need to figure out what this should be exactly
    pros::delay(10);
}