#include "main.h"
#include "globals.hpp"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void activateEndgame(){
    if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2)){
        // pros::c::adi_digital_write(2, false); // B is the ADI port and false is mapped to the LOW value, might need to change this depending on how endgame is set up
        piston1.set_value(true);
        piston2.set_value(true); // might be as simple as this, I think the previous way is the C way to do it
        pros::delay(1000);
        piston1.set_value(false);
        piston2.set_value(false);
    }
}