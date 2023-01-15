#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
bool fireCatapult = false;
bool canFire = false;

void move_catapult(double speed){
  catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);

  // loading if statement
  if (!catapult_switch.get_value()){
    catapultMotor.move_velocity(speed);
    pros::delay(10);
  }else if (catapult_switch.get_value()){ // executes and tells catapult to stop at bottom
    catapultMotor.move_velocity(0);  
    fireCatapult = false; 
    canFire = true; // to prevent pre-firing (press button before fully down and then shoots)
  }

  if (master.get_digital(DIGITAL_R1) && canFire) fireCatapult = true;

  if (fireCatapult && catapult_switch.get_value()){
    catapultMotor.move_velocity(600);
  } // else if (!catapult_switch.get_value()) catapultMotor.move_velocity(0); this should not be necessary
  
}

void auton_catapult(){ // this function fires the catapult and sets it back to loading position
  catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  // load_catapult(600);
  // fire_catapult();
  // load_catapult(600);
}   
