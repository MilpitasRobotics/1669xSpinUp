#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

// bool asdf = true; //change bool name later idkwhat to put
void move_catapult(){
  catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  if (master.get_digital(DIGITAL_R1)){
    while (!catapult_switch.get_value()){
      catapultMotor.move_velocity(600);
    }
    catapultMotor.move_velocity(0); 
  }
  if (master.get_digital(DIGITAL_R2)){
    while(catapult_switch.get_value()){
      catapultMotor.move_velocity(600);
    }
    pros::delay(500); // catapult should fire in this time period, might not be necessary but I think so because the motor is in hold
    catapultMotor.move_velocity(0);
  }
    // while (!catapult_switch.get_value() && asdf){
    //   catapultMotor.move_velocity(-20);
    //   }
    // if (catapult_switch.get_value()){
    //   asdf = false;
    //   if(master.get_digital(DIGITAL_R1)){ // catapult code should work smt like this, need to confirm w/ Eugene how exactly it works
    //    catapultMotor.move_velocity(20); // test to see if 20 velocity is right
    //    pros::delay(500);
    //    catapultMotor.move_velocity(0);
    //    asdf = true; 
    // }
    // }
}

void auton_catapult(){
  catapultMotor.move_velocity(600);
  pros::delay(500);
  catapultMotor.move_velocity(0);
}