#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
bool fireCatapult = false;
bool canFire = false;
bool stop = true; // this code might work fine without this boolean bc of the positioning of if statements

void move_catapult(double speed){
  catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);

  // loading if statement
  if (!catapult_switch.get_value()){
    catapultMotor.move_velocity(speed);
    canFire = false;
    pros::delay(10);
  }else if (stop && catapult_switch.get_value()){ // executes and tells catapult to stop at bottom
    catapultMotor.move_velocity(0);  
    fireCatapult = false; 
    canFire = true; // to prevent pre-firing (have to wait for arm to be fully down before pressing this to fire)
  }

  if (master.get_digital(DIGITAL_R1) && canFire) {
    fireCatapult = true;
    stop = false;
  }

  if (fireCatapult && catapult_switch.get_value()){
    catapultMotor.move_velocity(600);
    stop = true;
  } // else if (!catapult_switch.get_value()) catapultMotor.move_velocity(0); this should not be necessary
  
}

void auton_catapult(){ // this function fires the catapult and sets it back to loading position
  catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  // load_catapult(600);
  // fire_catapult();
  // load_catapult(600);
}   
