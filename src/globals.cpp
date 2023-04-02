#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

pros::Motor intakeRoller(9, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::ADIDigitalIn catapult_switch ('H'); 
pros::ADIDigitalOut pistonintake ('E');
pros::ADIDigitalOut autonBoost('F');
pros::Motor catapultMotor(1); 

bool toggle = false; 
bool toggle2 = false;
