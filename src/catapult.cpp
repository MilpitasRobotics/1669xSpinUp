#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
bool fireCatapult = false;
bool canFire = false;
bool stop = true; // this code might work fine without this boolean bc of the positioning of if statements
bool isEnabled = true;
int counter = 0;
bool oldPress = false;
bool moveCata = false;

void move_catapult(double speed){
  // this version if limit switch gets pressed twice
  catapultMotor.set_brake_mode(MOTOR_BRAKE_COAST);

  if(master.get_digital_new_press(DIGITAL_B)) isEnabled = !isEnabled; // pressing B on the controller will toggle catapult on/off 
  
  if(!isEnabled) catapultMotor.move_velocity(0);

  if (!catapult_switch.get_value() && isEnabled){
    catapultMotor.move_velocity(600);
  }

  if (catapult_switch.get_value()){
    if (!oldPress) counter++;
    oldPress = true;
  } else {
    oldPress = false;
  }

  if(counter == 1){
    catapultMotor.move_velocity(0);
  } else if (counter == 2) counter = 0;

  if (master.get_digital_new_press(DIGITAL_R1) && counter == 1 && isEnabled) catapultMotor.move_velocity(600);
  // catapultMotor.set_brake_mode(MOTOR_BRAKE_COAST);
  // if(master.get_digital_new_press(DIGITAL_B)) isEnabled = !isEnabled; // pressing B on the controller will toggle catapult on/off 
  //
  // if(!isEnabled) catapultMotor.move_velocity(0);
  //
  // // loading if statement
  // if (!catapult_switch.get_value() && isEnabled){
  //   catapultMotor.move_velocity(speed);
  //   canFire = false;
  //   pros::delay(10);
  // }else if (stop && catapult_switch.get_value()){ // executes and tells catapult to stop at bottom
  //   catapultMotor.move_velocity(0);  
  //   fireCatapult = false; 
  //   canFire = true; // to prevent pre-firing (have to wait for arm to be fully down before pressing this to fire)
  // }
  //
  // if (master.get_digital(DIGITAL_R1) && canFire) {
  //   fireCatapult = true;
  //   stop = false;
  // }
  //
  // if (fireCatapult && catapult_switch.get_value() && isEnabled){
  //   while(catapult_switch.get_value())catapultMotor.move_velocity(600);
  //   stop = true;
  // } // else if (!catapult_switch.get_value()) catapultMotor.move_velocity(0); this should not be necessary
}

void fire_catapult(){ // this function fires the catapult and sets it back to loading position
  catapultMotor.set_brake_mode(MOTOR_BRAKE_COAST);
  while(catapult_switch.get_value()) catapultMotor.move_velocity(600);
  catapultMotor.move_velocity(0);
  stopCata = true;
}   
