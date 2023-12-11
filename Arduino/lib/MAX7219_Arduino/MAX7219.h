#ifndef _MAX7219_H_
#define _MAX7219_H_

#include "Arduino.h"

// register definition
#define max7219_reg_noop        0x00
#define max7219_reg_digit0      0x01
#define max7219_reg_digit1      0x02
#define max7219_reg_digit2      0x03
#define max7219_reg_digit3      0x04
#define max7219_reg_digit4      0x05
#define max7219_reg_digit5      0x06
#define max7219_reg_digit6      0x07
#define max7219_reg_digit7      0x08
#define max7219_reg_decodeMode  0x09
#define max7219_reg_intensity   0x0a
#define max7219_reg_scanLimit   0x0b
#define max7219_reg_shutdown    0x0c
#define max7219_reg_displayTest 0x0f

// Register initial configuration values
#define decodeMode_reg_config 0x00 // No decode for digits 7-0
#define intensity_reg_config 0x02 // 0x00 - 0x0F
#define scanLimit_reg_config 0x07 // display all digits
#define shutdown_reg_config 0x01 // normal operation
#define displayTest_reg_config 0x00 // normal operation

class MAX7219
{
  public:
    MAX7219(uint8_t din, uint8_t cs, uint8_t clk);
    void init();
    void clear();
    void sendData(uint8_t reg_address, uint8_t data);
    void switchLED(uint8_t column, uint8_t row, uint8_t data);

   private:
    uint8_t din;
    uint8_t cs;
    uint8_t clk;
    uint8_t frame_buffer[8]; // assign 64 bits (8x8 matrix) of memory to hold the states of LEDs
};

#endif