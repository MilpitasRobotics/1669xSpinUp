#include "main.h"
#include "globals.hpp"

// This code is not working need to figure out what is going on

int reverse1 = 1; // determines the direction of the conveyor (-1 is intake, 1 is outtake)
bool conveyor_lock = false;
bool conveyor_up = false; // determines whether conveyor will move or not

void move_conveyor(){ //driver control
  if (master.get_digital(DIGITAL_L1)) { // this conditional covers stopping and starting the conveyer
    reverse1 = -1; // sets direction of conveyor to intake
    conveyor_up = !conveyor_up; // switches the value of conveyer_up (false --> true, true --> false), takes care of turning the conveyer on and off
    conveyor_lock = true;
    while(master.get_digital(DIGITAL_L1))pros::delay(10); // holding down L1 will cause this delay statement to execute until it is released
  }
  else if (!master.get_digital(DIGITAL_L1) && conveyor_lock) { // this elif statement will execute after L1 is held down since L1 will no longer be pressed and conveyer_lock == true
    reverse1 = 1; // sets direction of conveyor to outtake
    conveyor_lock = false; // sets conveyor_lock back to false so that this elif statement does not execute next time function is called
  }

  if (conveyor_up && catapult_switch.get_value()) // if the catapult is not in loading position, the intake will not run to prevent jamming
    conveyorRoller.move_velocity(600*reverse1);
  else
    conveyorRoller.move_velocity(0);
}