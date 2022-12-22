#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

// bool asdf = true; //change bool name later idkwhat to put
void move_catapult(){
  catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  load_catapult();
  if (master.get_digital(DIGITAL_R1)){
    while(catapult_switch.get_value()){
      catapultMotor.move_velocity(600);
    }
    catapultMotor.move_velocity(0);
  }
}

void auton_catapult(){ // this function fires the catapult and sets it back to loading position
  catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  load_catapult();
  while(catapult_switch.get_value()){
    catapultMotor.move_velocity(600);
  }
  catapultMotor.move_velocity(0);
  load_catapult();
}  
    
void load_catapult(){
 while (!catapult_switch.get_value()){
      catapultMotor.move_velocity(600);
    }
  catapultMotor.move_velocity(0);  
}