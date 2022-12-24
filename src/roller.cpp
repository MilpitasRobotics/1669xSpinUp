#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void move_roller(){

while (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2)){
    conveyorRoller.move_velocity(-600); 
    pros::delay(10);
}
conveyorRoller.move_velocity(0);
}

void auton_roller(){
    conveyorRoller.move_relative(50, 50); // need to figure out what this should be exactly
    pros::delay(10);
}