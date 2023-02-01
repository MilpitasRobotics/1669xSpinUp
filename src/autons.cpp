#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "globals.hpp"
#include "endgame.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/llemu.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include <cmath>


//For Example Now Drive speed For everything is 75
const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 75;
const int SWING_SPEED = 75;

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(127, 127); // Reset this to default
  chassis.set_slew_distance(1, 1);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.68, 0, 5.25, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.65, 0, 5.25, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5.35, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


void leftAwp() { // starts off with the roller then avoids discs to shoot into the high goal
  chassis.set_swing_pid(ez::LEFT_SWING, -30, TURN_SPEED);
  chassis.wait_drive();
  auton_roller();
  chassis.set_drive_pid(4,DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(40,DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30,DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-35, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();
  fire_catapult(); 
  // load_catapult(600);
  auton_intake();
  fire_catapult();
}

void rightAwp(){ // starts off with the right side, moves forward shoots, comes back gets the roller
  chassis.set_drive_pid(22, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-38, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 0, TURN_SPEED);
  chassis.wait_drive();
  auton_roller();
}

void soloAwp() { // same as left AWP but added turn, move forward, turn again, get roller
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(8, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-34, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-35, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  chassis.set_swing_pid(ez::RIGHT_SWING, -135, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-70, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  chassis.set_turn_pid(-100, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();
  }

void justRoller(){
 
}

void testFunc(){
  pros::delay(100);
  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(200);

}

void progSkills(){ // remember to switch all signs (assumes that task for loading cata works)
  chassis.set_drive_pid(2, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_until(28);
  intake_toggle(false);
  chassis.wait_drive();
  auton_roller();
  chassis.set_drive_pid(-16, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-64, 127);
  chassis.wait_until(-40);
  chassis.set_max_speed(DRIVE_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(100);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(100);
  intake_toggle(true);
  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(100);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(100);
  intake_toggle(true);
  pros::delay(100);
  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(100);
  chassis.set_drive_pid(64, 127);
  chassis.wait_until(40);
  chassis.set_max_speed(DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(100);
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(100);
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  pros::delay(100);
  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(100);
  intake_toggle(true);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(100);
  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_until(20);
  intake_toggle(false);
  chassis.wait_drive();
  auton_roller();
  chassis.set_drive_pid(-36, DRIVE_SPEED); 
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  chassis.set_drive_pid(72, 127);
  chassis.wait_until(60);
  chassis.set_max_speed(DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  // fire endgame
  endgameToggle(true); 
}



/* 
// . . .
// Make your own autonomous functions here!
// . . .
*/
