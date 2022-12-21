#include "main.h"
#include "globals.hpp"


int reverse1 = 1; // determines the direction of the conveyor (-1 is intake, 1 is outtake)
bool conveyor_lock = false;
bool conveyor_up = false; // determines whether conveyor will move or not

void move_conveyor(){ //driver control
  if (master.get_digital(DIGITAL_R2)) { // this conditional covers stopping and starting the conveyer
    reverse1 = -1; // sets direction of conveyor to intake
    conveyor_up = !conveyor_up; // switches the value of conveyer_up (false --> true, true --> false), takes care of turning the conveyer on and off
    conveyor_lock = true;
    while(master.get_digital(DIGITAL_R2))pros::delay(10); // holding down R2 will cause this delay statement to execute until it is released
  }
  else if (!master.get_digital(DIGITAL_R2) && conveyor_lock) { // this elif statement will execute after R2 is held down since R2 will no longer be pressed and conveyer_lock == true
    reverse1 = 1; // sets direction of conveyor to outtake
    conveyor_lock = false; // sets conveyor_lock back to false so that this elif statement does not execute next time function is called
  }

  if (conveyor_up)
    conveyorRoller.move_velocity(600*reverse1);
  else
    conveyorRoller.move_velocity(0);
}

/* our code
bool isPressed = false;
if (master.get_digital(DIGITAL_L1)){ // need to test 
        intakeMotor.move_velocity(20);
        isPressed = true;
    }
    pros::delay(500); // next if statement will execute so testing to see speed of intake
    if (isPressed && intakeMotor.get_actual_velocity() > 0 && isBeingHeld(DIGITAL_L1)){ // need to add conditon to check if button is held down should be && smt else
        intakeMotor.move_velocity(-20);
        isPressed = true;
    } 
    if (master.get_digital(DIGITAL_L1) && isPressed){ 
        intakeMotor.move_velocity(0);
        isPressed = false;
    }
*/
