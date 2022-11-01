#include "main.h"

//instead of plotting manual values for each motor we use this helper function to simplify it
void setDriveMotors(int left,int right) {
    leftDrive1 = left;
    leftDrive2 = left;
    leftDrive3 = left;
    rightDrive1 = right;
    rightDrive2 = right;
    rightDrive3 = right;
}


//stuff that makes the motor move we take the values of the controller and plug it into the motor values
void MotorDrive() {
    int x = controller.get_analog(ANALOG_LEFT_X);
    int y = controller.get_analog(ANALOG_LEFT_Y);

    if(abs(x) < 10)
        x = 0;
    if(abs(y) < 10)
        y = 0;
    int right = (y - x);
    int left = (y + x);

    setDriveMotors(left, right);
}