#include "main.h"
#include "pros/motors.h"
// Helper Functions

//instead of plotting manual values for each motor we use this helper function to simplify it
void setDriveMotors(int left,int right) {
    leftFront = left;
    leftMiddle = left;
    leftBack = left;
    rightFront = right;
    rightMiddle = right;
    rightBack = right;
}

// resets all of the motor encoders
/*
According to Google:
The encoders measure how far the wheels have turned, and therefore, how far the robot has moved. 
The turning of the wheel is what propels the robot forward.
*/
void resetDriveEncoders(){
    leftFront.tare_position();
    leftMiddle.tare_position();
    leftBack.tare_position();
    rightFront.tare_position();
    rightMiddle.tare_position();
    rightBack.tare_position();
}

// Averages out the position/encoder values of all the motors in case the position of individual motors is screwed up
double avgdDriveEncodervalue(){
    return (fabs(leftFront.get_position()) + 
            fabs(leftMiddle.get_position()) + 
            fabs(leftBack.get_position()) + 
            fabs(rightFront.get_position()) + 
            fabs(rightMiddle.get_position()) + 
            fabs(rightBack.get_position())) / 6;
}



//stuff that makes the motor move we take the values of the controller and plug it into the motor values
void MotorDrive() {
    int x = controller.get_analog(pros ::E_CONTROLLER_ANALOG_LEFT_X);
    int y = controller.get_analog(pros ::E_CONTROLLER_ANALOG_LEFT_Y);

    //deadzone
    if(abs(x) < 10)
        x = 0;
    if(abs(y) < 10)
        y = 0;

    //this works turning
    int right = (y - x);
    int left = (y + x);

    setDriveMotors(left, right);
}

//Braking Functions

void braking(){
    int brake = controller.get_digital(DIGITAL_A);

    if (brake == true){
        leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        leftMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rightMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }
    else{
        leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        leftMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        rightMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    }
}

// Autonomous Functions
void translate(int units, int voltage){
    // determine the direction of motion (either 1 or -1)
    int direction = abs(units) / units; 

    // resets motor encoders so that the robot can move however many units specified
    resetDriveEncoders();

    // drive forward until units are reached
    while(avgdDriveEncodervalue() < abs(units)){ // use fabs because abs only works with ints
        setDriveMotors(voltage * direction, voltage * direction);
        pros::delay(10);
    }
    
    // brief brake to stop momentum of robot (sets direction of motor opposite to motion for a short period of time)
    setDriveMotors(-10 * direction, -10 * direction);
    pros::delay(75); // tentative delay value, have to use the weight of the robot to determine this

    // set drive back to neutral
    setDriveMotors(0,0);
}