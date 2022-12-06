#include "main.h"

pros::Motor conveyor(9, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
int reverse1 = 1;
bool conveyor_lock = false;
bool conveyor_up = false;

void move_conveyor(){ //driver control
  if (master.get_digital(DIGITAL_R2)) {
    reverse1 = -1;
    conveyor_up = !conveyor_up;
    conveyor_lock = true;
    while(master.get_digital(DIGITAL_R2))pros::delay(10);
  }
  else if (!master.get_digital(DIGITAL_R2) && conveyor_lock==true) {
    reverse1 = 1;
    conveyor_lock = false;
  }

  if (conveyor_up)
    conveyor.move_velocity(600*reverse1);
  else
    conveyor.move_velocity(0);
}

/* our code
bool isPressed = false;
if (master.get_digital(DIGITAL_L1)){ // need to test 
        intakeMotor.move_velocity(20);
        isPressed = true;
    }
    pros::delay(500); // next if statement will execute so testing to see speed of intake
    if (isPressed && intakeMotor.get_actual_velocity() > 0 && isBeingHeld(DIGITAL_L1)){ // need to add conditon to check if button is held down should be && smt else
        intakeMotor.move_velocity(-20);
        isPressed = true;
    } 
    if (master.get_digital(DIGITAL_L1) && isPressed){ 
        intakeMotor.move_velocity(0);
        isPressed = false;
    }
*/
