#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

pros::ADIDigitalIn catapult_switch ('A'); // need to check if this port is available in person
pros::Motor catapultMotor(6); // need to check if this port is available


bool asdf = true; //change bool name later idkwhat to put
void move_catapult(){

    while (!catapult_switch.get_value() && asdf){
      catapultMotor.move_velocity(-20);
      }
    if (catapult_switch.get_value()){
      asdf = !asdf;
      if(master.get_digital(DIGITAL_R1)){ // catapult code should work smt like this, need to confirm w/ Eugene how exactly it works
       catapultMotor.move_velocity(20); // test to see if 20 velocity is right
       pros::delay(500);
       asdf = !asdf; 
    }
    }
}