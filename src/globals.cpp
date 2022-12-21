#include "main.h"
#include "pros/misc.h"
pros::Motor conveyorRoller(9, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::ADIDigitalIn catapult_switch ('A'); 
pros::Motor catapultMotor(21); 