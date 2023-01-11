#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "autons.hpp"
#include "endgame.hpp"
#include "catapult.hpp"
#include "globals.hpp"
#include "pros/motors.h"
/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {10, 6, 2} // port 1 was malfunctioning need to figure out what is going on

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{-13, -15, -16}

  // IMU Port
  ,19

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.6666667  // 36:48 where the 48 is powered so 36/48

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // configure endgame
  // pros::c::adi_pin_mode(2, 0x01); // 2 is mapped to the ADI port B and 0x01 is the value for a digital output
  // pros::c::adi_digital_write('B', true); // B is the ADI port and true is mapped to the HIGH value

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(2.5, 1); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  need to change this for smooth controlling
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!
  piston1.set_value(true);
  piston2.set_value(true);

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);
  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("PID with error", autonWithError),
    Auton("Tune PID", tunePIDFunc),
    Auton("Solo AWP Left", leftSoloAwp), 
    Auton("Solo AWP Right", rightSoloAwp),
    Auton("Right Side", rightSide),  
    Auton("Left Side", leftSide),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();


}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_gyro(); 
  chassis.reset_drive_sensor(); 
  pros::Task load(load_catapult_auton);
  chassis.set_drive_brake(MOTOR_BRAKE_COAST); 
  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
  load.remove();
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);  
  while (true) {
    // chassis.tank(); // Tank control
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade
    
    // . . .
    // Put more user control code here!
    // . . .
    move_catapult();    
    move_conveyor_roller();
    // activateEndgame();
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
