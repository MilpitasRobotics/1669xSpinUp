#include "main.h"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "intakeRoller.hpp"

int direction = 1; // determines the direction of the intake (-1 is intake, 1 is outtake)
bool intake_lock = false;
bool intake_on = false; // determines whether intake will move or not
bool roller_on = false;


void move_intake_roller(){ // driver control
  // L1 control
  if (master.get_digital_new_press(DIGITAL_L1)) { // only toggles intake on/off if button was not pressed last time this function was called
    intake_on = !intake_on;
  }

  // sets the direction of intake
  if (master.get_digital(DIGITAL_L2)) direction = -1;
  else direction = 1;

  // roller code
  if (master.get_digital(DIGITAL_R2)) roller_on = true;
  else roller_on = false;

  if (intake_on && catapult_switch.get_value()) // if the catapult is not in loading position, the intake will not run to prevent jamming
    intakeRoller.move_velocity(-600 * direction);
  else if (roller_on && catapult_switch.get_value()) // activates roller
    intakeRoller.move_velocity(600);
  else
    intakeRoller.move_velocity(0);
}

void auton_roller(){
  intakeRoller.move_relative(250, 600);
}

void skills_roller(){
  pros::delay(rollerTime);
}

void skills_roller_toggle(bool state){
  if (state)
    intakeRoller.move_velocity(600);
  else
    intakeRoller.move_velocity(0);
}

void auton_intake(){
 intake_toggle(true);
 pros::delay(500);
 intake_toggle(false);
}

void intake_toggle(bool state){
  if (state)
    intakeRoller.move_velocity(-600);
  else
    intakeRoller.move_velocity(0);
}

