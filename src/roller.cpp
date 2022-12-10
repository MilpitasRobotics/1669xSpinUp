#include "main.h"
#include "pros/misc.h"

pros::Motor rollerMotor(5);

void move_roller(){
while (master.get_digital(DIGITAL_L1)){
    rollerMotor.move_velocity(50); // need to figure out which speed is best for this
}
}

void auton_roller(){
    rollerMotor.move_relative(50, 50); // need to figure out what this should be exactly
}