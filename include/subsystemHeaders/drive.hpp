#include "main.h"


//calling all functions made in drive.cpp

// Helper Functions
void setDriveMotors(int left, int right);

void setTurnMotorSwing(int turn);

void setTurnMotorPoint(int turn);

void resetDriveEncoders();

double avgdDriveEncodervalue();

// Driver Control Functions
void MotorDrive();
void braking();

// Autonomous functions
void translate(int units, int voltage);
void turnSwing(int turnUnits);
void turnPoint(int turnUnits);

