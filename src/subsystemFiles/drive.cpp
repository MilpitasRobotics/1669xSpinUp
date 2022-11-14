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

void setTurnMotorSwing(int turn){ // robot will turn right if given a positive value and will turn left if given a negative value
    if (turn > 0){ 
        leftFront = turn;
        leftMiddle = turn;
        leftBack = turn;
    }else if (turn < 0){
        turn = abs(turn);
        rightFront = turn;
        rightMiddle = turn;
        rightBack = turn;
    }
    
}

void setTurnMotorPoint(int turn){ // robot will turn right if given a positive value and will turn left if given a negative value
    if (turn > 0){ 
        leftFront = turn;
        leftMiddle = turn;
        leftBack = turn;
        rightFront = -turn;
        rightMiddle = -turn;
        rightBack = -turn; 
    }else if (turn < 0){
        turn = abs(turn);
        rightFront = turn;
        rightMiddle = turn;
        rightBack = turn;
        leftFront = -turn;
        leftMiddle = -turn;
        leftBack = -turn;
    }
    
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

    //this works movement 
    int right = (y - x);
    int left = (y + x);

    setDriveMotors(left, right);
}

//Braking Functions

void braking(){
    int brake = controller.get_digital(DIGITAL_A);

    //rewrote this to become an emergency brake, actual braking function will be moving backwards on controller
    if (brake == 0){
        leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        leftMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        rightMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        leftFront.brake();
        leftMiddle.brake();
        leftBack.brake();
        rightFront.brake();
        rightMiddle.brake();
        rightBack.brake();
    }
    else{
        leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_INVALID);
        leftMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_INVALID);
        leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_INVALID);
        rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_INVALID);
        rightMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_INVALID);
        rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_INVALID);
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

void turnPoint(int turnUnits){
    pros::delay(1000);
    setTurnMotorPoint(turnUnits);
    pros::delay(1000);
}

void turnSwing(int turnUnits){
    pros::delay(1000);
    setTurnMotorSwing(turnUnits);
    pros::delay(1000);
}