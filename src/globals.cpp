#include "main.h"
#include "pros/misc.h"

pros::Motor conveyorRoller(10, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::ADIDigitalIn catapult_switch ('B'); 
pros::ADIDigitalOut piston1 ('C');
pros::ADIDigitalOut piston2 ('D');
pros::Motor catapultMotor(21); 