#include "main.h"
#include "globals.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

pros::ADIDigitalOut piston1('B');
void activateEndgame(){
    // bool activate = master.get_digital(DIGITAL_LEFT) && master.get_digital(DIGITAL_A);
    // if (activate && master.get_digital(DIGITAL_L1)){
       // piston1.set_value(false);
     //   pros::delay(1000);
       // piston1.set_value(true);
    //} else if (activate && master.get_digital(DIGITAL_R1)){
    //    piston2.set_value(false); 
    //    pros::delay(1000);
    //    piston2.set_value(true);
    //}

    
}

void endgameToggle(bool toggle){
 piston1.set_value(toggle);
}
