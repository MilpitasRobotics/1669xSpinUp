#include "main.h"
#include "globals.hpp"
#include "endgame.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

pros::ADIDigitalOut piston1('B');
void activateEndgame(){
    if(master.get_digital(DIGITAL_LEFT) && master.get_digital(DIGITAL_A)){
      endgameToggle(true);
    }
}

void endgameToggle(bool toggle){
 piston1.set_value(toggle);
}
