#include "main.h"
#include "pros/misc.h"

pros::ADIDigitalIn catapult_switch ('B'); 
pros::ADIDigitalOut piston1 ('C');
pros::ADIDigitalOut piston2 ('D');
pros::Motor catapultMotor(21); 