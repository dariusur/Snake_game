/*
* Run this example to test LED matrix module.
* Each LED lights up one by one filling the entire screen.
* After each fill the intensity is increased and the filling procedure is repeated.
* When the intensity reaches maximum new loop begins.
*/

#include "MAX7219.h"

const uint8_t DIN = 5, CS = 6, CLK = 7; // DIN, CS, CLK pins of MAX7219 module

MAX7219 matrix(DIN, CS, CLK); // define module

void setup(){
  matrix.init(); // module initialize
}

void loop(){
  for(uint8_t intensity=0;intensity<=15;intensity++){
    matrix.sendData(max7219_reg_intensity, intensity);
    for(uint8_t i=0;i<8;i++){
      for(uint8_t j=0;j<8;j++){
        matrix.switchLED(i,j,1);
        delay(50);
      }
    }
    matrix.clear();
  }
}