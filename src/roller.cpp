#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

pros::Motor conveyorRoller(10, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

void move_roller(){
while (master.get_digital(DIGITAL_R2)){
    conveyorRoller.move_velocity(-600); 
    pros::delay(10);
}
conveyorRoller.move_velocity(0);
}

void auton_roller(){
    conveyorRoller.move_relative(50, 50); // need to figure out what this should be exactly
    pros::delay(10);
}