#include "main.h"


//calling all functions made in drive.cpp

// Helper Functions
void setDriveMotors(int left, int right);

void resetDriveEncoders();

double avgdDriveEncodervalue();

// Driver Control Functions
void MotorDrive();
void braking();

// Autonomous functions
void translate(int units, int voltage);

