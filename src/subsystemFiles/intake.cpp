#include "main.h"
#include "okapi/api.hpp"


void setIntake(int power) {
    intake_motors = power;
}


void setIntakeMotor() {
    int intakePower = 0;
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
        intakePower = -127;
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
        intakePower = 127;
    else{}
        intakePower = 0;
}