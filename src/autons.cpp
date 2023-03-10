#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "globals.hpp"
#include "endgame.hpp"
#include "intakeRoller.hpp"
#include "catapult.hpp"
#include "main.h"


//For Example Now Drive speed For everything is 75
const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 75;
const int SWING_SPEED = 75;

int rollerTime = 750;
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


void leftAwp() { // starts off with the roller then shoots 5 discs into the goal
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(100);
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(35, 80);
  chassis.wait_drive();
  pros::delay(750);
  intake_toggle(false);
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();
  fire_catapult();
}

void rightAwp(){ // gets roller then shoots 5 discs into the high goal
  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 95, SWING_SPEED);
  chassis.wait_drive();
  auton_roller();
  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(225, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(2, DRIVE_SPEED);
  intake_toggle(true);
  chassis.set_drive_pid(-30, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(750);
  intake_toggle(false);
  chassis.set_turn_pid(116, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(4.8, DRIVE_SPEED);
  fire_catapult();
  pros::delay(500);
  chassis.set_turn_pid(220, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(2500);
  intake_toggle(true);
  chassis.set_drive_pid(-35, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(500);
  intake_toggle(false);
  chassis.set_turn_pid(140, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(750);
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  fire_catapult();
}

void soloAwp() { // same as left AWP but added turn, move forward, turn again, get roller
  chassis.set_drive_pid(-3, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  pros::delay(500);
  chassis.set_drive_pid(18, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-14, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(200);
  chassis.set_drive_pid(-10, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(-15, 80);
  chassis.wait_until(-10);
  chassis.set_max_speed(30);
  chassis.wait_drive();
  chassis.set_drive_pid(-30,35);
  chassis.wait_drive();
  pros::delay(750);
  intake_toggle(false);
  chassis.set_turn_pid(-35, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(7, DRIVE_SPEED);
  chassis.wait_drive();
  //chassis.set_drive_pid(4, DRIVE_SPEED);
  fire_catapult();
  pros::delay(800);
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  intake_toggle(true);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-70, 80);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, -90, SWING_SPEED);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_drive_pid(-10, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  // chassis.set_drive_pid(-4, DRIVE_SPEED);
  // chassis.wait_drive();
  // auton_roller();
  // chassis.set_drive_pid(4,DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-45,DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-180,TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-30,DRIVE_SPEED);
  // chassis.wait_until(-15);
  // intake_toggle(true);
  // chassis.wait_drive();
  // intake_toggle(false);
  // chassis.set_turn_pid(-45, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(10, DRIVE_SPEED);
  // fire_catapult();
  // pros::delay(100);
  // chassis.set_swing_pid(ez::RIGHT_SWING, -135, SWING_SPEED);
  // chassis.wait_drive();
  // intake_toggle(true);
  // chassis.set_drive_pid(-48, DRIVE_SPEED);
  // chassis.wait_drive();
  // intake_toggle(false);
  // chassis.set_turn_pid(-45, TURN_SPEED); // finish rest of path, still have to shoot the second time
  // chassis.wait_drive();
  // chassis.set_drive_pid(6, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-70, TURN_SPEED);
  // chassis.wait_drive();
  // fire_catapult();
  // chassis.set_turn_pid(-100, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(36, DRIVE_SPEED);
  // chassis.wait_drive();
  }

void justRoller(){
  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 95, SWING_SPEED);
  chassis.wait_drive();
  auton_roller();
  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(225, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(-30, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(750);
  intake_toggle(false);
  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  
}

void testFunc(){
  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();
}

void progSkills(){
  skills_roller_toggle(true);
  chassis.set_drive_pid(-2.5, DRIVE_SPEED);
  chassis.wait_drive();
  skills_roller(); 
  pros::delay(350);
  chassis.set_drive_pid(17, 50);
  chassis.wait_drive();
  pros::delay(250);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(-26, 50);
  chassis.wait_drive();
  skills_roller_toggle(true);
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
  skills_roller();
  pros::delay(350);
  chassis.set_drive_pid(9.5, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-4, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(61, DRIVE_SPEED); // might need to tune this to make the next shot work
  intake_toggle(true);
  chassis.wait_drive();
  chassis.set_turn_pid(10, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(500);
  intake_toggle(true);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(750);
  chassis.set_drive_pid(-34.5, 55);
  chassis.wait_drive();
  pros::delay(250);
  chassis.set_drive_pid(33.5, 100);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_turn_pid(10, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(500);
  intake_toggle(true);
  chassis.set_turn_pid(-35, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-35, 80);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(-36, 45);
  chassis.wait_drive();
  pros::delay(500);
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(5.25, DRIVE_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(750);
  // chassis.set_drive_pid(-0.25, DRIVE_SPEED);
  // chassis.wait_drive();
  intake_toggle(true);
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-46.5, 70);
  chassis.wait_drive();
  pros::delay(750);
  chassis.set_turn_pid(-98, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  intake_toggle(false);
  pros::delay(500);
  chassis.set_turn_pid(-53, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(-61, 70);
  chassis.wait_until(35);
  intake_toggle(false);
  chassis.set_max_speed(40);
  chassis.wait_until(35.5);
  intake_toggle(true);
  chassis.wait_drive();
  pros::delay(750);
  intake_toggle(false);
  chassis.set_turn_pid(-70, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(250);
  chassis.set_drive_pid(42, 90);
  chassis.wait_until(8);
  intakeRoller.move_velocity(600);
  chassis.wait_drive();
  chassis.set_turn_pid(-72, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(600);
  chassis.set_turn_pid(-70, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(-66, 85);
  chassis.wait_until(42);
  chassis.set_max_speed(65);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_drive_pid(-4.5, 85);
  chassis.wait_drive();
  pros::delay(700);
  skills_roller();
  chassis.set_drive_pid(27.25, DRIVE_SPEED);
  chassis.wait_until(15);
  intake_toggle(true);
  chassis.wait_drive();
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-29.5, 55);
  chassis.wait_until(-20);
  skills_roller_toggle(true);
  chassis.wait_drive();
  pros::delay(150);
  skills_roller();
  chassis.set_drive_pid(5, DRIVE_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_turn_pid(-196.5, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(75, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-175, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(500);
  chassis.set_drive_pid(1.5, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-270, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  pros::delay(250);
  chassis.set_drive_pid(-32, 55);
  chassis.wait_drive();
  chassis.set_drive_pid(32, 90);
  chassis.wait_drive();
  intake_toggle(false);
  chassis.set_turn_pid(-175, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(500);
  fire_catapult();
  pros::delay(500);
  intake_toggle(true);
  chassis.set_turn_pid(-215, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-35, 85); // here
  chassis.wait_drive();
  pros::delay(500);
  chassis.set_turn_pid(-315, TURN_SPEED);
  chassis.wait_drive();
  intake_toggle(true);
  chassis.set_drive_pid(-36, 50);
  chassis.wait_drive();
  pros::delay(500);
  intake_toggle(false);
  intakeRoller.move_velocity(600);
  chassis.set_turn_pid(-225, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED); // was 7.5 before but hit the barrier
  chassis.wait_drive();
  fire_catapult();
  pros::delay(750);
  intake_toggle(true);
  chassis.set_turn_pid(-360, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-46.5, 55); // changed to match other side and avoid hitting barrier for shot
  chassis.wait_drive();
  pros::delay(750);
  chassis.set_turn_pid(-278, TURN_SPEED);
  chassis.wait_drive();
  fire_catapult();
  pros::delay(250);
  chassis.set_turn_pid(-267, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-56.5, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-315, TURN_SPEED);
  chassis.wait_drive();
  // endgameToggle(true);
  // list of things i changed, move forward less for barrier shot, more time on last 2 rollers, drive back more on last line of 3 to avoid hitting the barrier, change angle and distance travelled for endgame
}


/* 
// . . .
// Make your own autonomous functions here!
// . . .
*/
