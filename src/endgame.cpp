#include "main.h"
#include "globals.hpp"
#include "pros/adi.h"
#include "pros/misc.h"

void activateEndgame(){
    if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2)){
        pros::c::adi_digital_write(2, false); // B is the ADI port and false is mapped to the LOW value, might need to change this depending on how endgame is set up
    }
}