#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();
void leftSide();
void leftsoloawp();
void test_constants(double inches);
double convert_encoder_values(int port);
bool isBeingHeld(pros::controller_digital_e_t button);

void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();