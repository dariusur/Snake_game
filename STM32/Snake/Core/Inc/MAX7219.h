#ifndef _MaxMatrix_H_
#define _MaxMatrix_H_

#include "stm32f4xx_hal.h"

// Register definitions
#define noop_reg_addr 0x00
#define digit0_reg_addr 0x01
#define digit1_reg_addr 0x02
#define digit2_reg_addr 0x03
#define digit3_reg_addr 0x04
#define digit4_reg_addr 0x05
#define digit5_reg_addr 0x06
#define digit6_reg_addr 0x07
#define digit7_reg_addr 0x08
#define decodeMode_reg_addr 0x09
#define intensity_reg_addr 0x0a
#define scanLimit_reg_addr 0x0b
#define shutdown_reg_addr 0x0c
#define displayTest_reg_addr 0x0f

// Register initial configuration values
#define decodeMode_reg_config 0x00 // No decode for digits 7-0
#define intensity_reg_config 0x02 // 0x00 - 0x0F
#define scanLimit_reg_config 0x07 // display all digits
#define shutdown_reg_config 0x01 // normal operation
#define displayTest_reg_config 0x00 // normal operation

class MAX7219
{
  public:
	MAX7219(SPI_HandleTypeDef *hspi);
    void init();
    void clear();
    void sendData(uint8_t reg_addr, uint8_t data);
    void switchLED(uint8_t col, uint8_t row, uint8_t value);

  private:
    uint8_t buffer[8];
  	SPI_HandleTypeDef *hspi;
};

#endif
