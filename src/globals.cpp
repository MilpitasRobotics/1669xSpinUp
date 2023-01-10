#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

pros::Motor conveyorRoller(9, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::ADIDigitalIn catapult_switch ('H'); 
pros::ADIDigitalOut piston1 ('C');
pros::ADIDigitalOut piston2 ('D');
pros::Motor catapultMotor(11); 
