#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

void leftSide();
void rightSide();
void leftSoloAwp();
void rightSoloAwp();
double encoderToInches(double encoderUnits);
void tunePIDFunc();
void autonWithError();

void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();
