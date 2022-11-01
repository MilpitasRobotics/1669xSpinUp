#include "main.h"
#include "okapi/api.hpp"


void setIntake(int velocity) {
    motorintake = velocity;
}


//think about math and booleans, if l1 isn't pressed, it's false, giving it a value of 0, if it is pressed, it's true, giving it a value of 1

void setIntakeMotor() {
    int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
}