#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "globals.hpp"
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

const double circum = 3.25*M_PI;
const double gear_ratio = 0.6;
const double inches_per_degree = circum/360; // drivetrain motors are 900 ticks/revolution 18:1



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


void leftSide() {
  //move back, wait 2 seconds to get roller, will implement roller code when it's done
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  pros::delay(100);

  //move foward towards the center line
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(50);

  //turn 45 degrees right, become parallel to the white line
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(50);

  //move to the middle, will measure later, make sure slew is on or we destory motors
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(50);

  //turn 90 degrees left to face the goal, will impliment shooting code
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(10);
  auton_catapult();
  pros::delay(10);
}


void leftSoloAwp() {
  //move back, wait 2 seconds to get roller, will implement roller code when it's done
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  pros::delay(100);

  //move foward towards the center line
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(50);

  //turn 45 degrees right, become parallel to the white line
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(50);

  //move to the middle, will measure later, make sure slew is on or we destory motors
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(50);

  //turn 90 degrees left to face the goal, will impliment shooting code
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(10);
  auton_catapult();
  pros::delay(10);
  //turn 90 degrees left, drive using reverse
  chassis.set_turn_pid(-90,TURN_SPEED);
  chassis.wait_drive();
  pros::delay(10);
  chassis.set_drive_pid(-24,DRIVE_SPEED);
  chassis.wait_drive();

  //turn 90 degrees right to have the thing rolling the roller facing the roller, then back up into roller
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();
  //roller code here
}

void rightSide(){
  //ROBOT MUST FACE TO THE LEFT
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  auton_roller();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  auton_catapult();
}

void rightSoloAwp(){
  //ROBOT MUST FACE TO THE LEFT
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  auton_roller();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  auton_catapult();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(45, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
  auton_roller();


}

/* 

// . . .
// Make your own autonomous functions here!
// . . .
*/

void tunePIDFunc(){
    chassis.set_drive_brake(pros::E_MOTOR_BRAKE_COAST);
    chassis.set_turn_pid(90, TURN_SPEED);
  double avgEncoderUnits = (pros::c::motor_get_encoder_units(16) + pros::c::motor_get_encoder_units(15) + pros::c::motor_get_encoder_units(13))/3.0;
  pros::lcd::print(1, "Encoder Units: %f", avgEncoderUnits);
  pros::lcd::print(2, "Inches traveled: %f", encoderToInches(avgEncoderUnits));
}

void autonWithError(){
    load_catapult();
    conveyor_toggle(true); 
    chassis.set_swing_pid(ez::RIGHT_SWING, -90, TURN_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(-40, DRIVE_SPEED);
    chassis.wait_drive();
    conveyor_toggle(false);
    chassis.set_turn_pid(180, TURN_SPEED);
    fire_catapult();

//  chassis.set_drive_pid(24, DRIVE_SPEED);
  //while (true){
      //pros::lcd::print(2, " Left Error: %f  Right Error: %f\n", chassis.leftPID.error, chassis.rightPID.error);
    //  pros::delay(10);
  //}
}


double encoderToInches(double encoderUnits){
  return encoderUnits*inches_per_degree/gear_ratio; 
}





