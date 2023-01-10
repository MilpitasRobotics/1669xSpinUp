#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"

int direction = 1; // determines the direction of the conveyor (-1 is intake, 1 is outtake)
bool conveyor_lock = false;
bool conveyor_on = false; // determines whether conveyor will move or not
bool roller_on = false;


void move_conveyor_roller(){ // driver control
  // L1 control
  if (master.get_digital_new_press(DIGITAL_L1)) { // only toggles conveyor on/off if button was not pressed last time this function was called
    conveyor_on = !conveyor_on;
  }

  // sets the direction of conveyor
  if (master.get_digital(DIGITAL_L2)) direction = -1;
  else direction = 1;

  // roller code
  if (master.get_digital(DIGITAL_R2)) roller_on = true;
  else roller_on = false;

  if (conveyor_on && catapult_switch.get_value()) // if the catapult is not in loading position, the intake will not run to prevent jamming
    conveyorRoller.move_velocity(-600 * direction);
  else if (roller_on) // activates roller
    conveyorRoller.move_velocity(-600);
  else
    conveyorRoller.move_velocity(0);
}

void auton_roller(){
  conveyorRoller.move_relative(60, 600);
}

void conveyor_toggle(bool state){
  if (state)
    conveyorRoller.move_velocity(-600);
  else
    conveyorRoller.move_velocity(0);
}

