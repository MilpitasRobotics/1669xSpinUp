#include "main.h"
#include "pros/misc.h"

pros::ADIDigitalIn catapult_switch ('A'); // need to check if this port is available in person
pros::Motor catapultMotor(6); // need to check if this port is available

void move_catapult(){

    while (!catapult_switch.get_value()){
      catapultMotor.move_velocity(20);
      }
    if (catapult_switch.get_value()){
      if(master.get_digital(DIGITAL_R1)){ // catapult code should work smt like this, need to confirm w/ Eugene how exactly it works
       catapultMotor.move_velocity(20); // test to see if 20 velocity is right 
    }
    }
}