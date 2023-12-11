/*
 * This is a lite version of the MaxMatrix library
 * written specifically for the Snake game on STM32 microcontroller.
 * Code adapted from https://github.com/riyas-org/max7219
 */

#ifndef _MaxMatrix_H_
#define _MaxMatrix_H_

#include "stm32f4xx_hal.h"

class MaxMatrix
{
  public:
    MaxMatrix(SPI_HandleTypeDef *hspi);
    void init();
    void clear();
    void sendData(uint8_t *reg_addr, uint8_t *data);
    void setIntensity(uint8_t *intensity);
    void setDot(uint8_t col, uint8_t row, uint8_t value);

  private:
    uint8_t noop_reg_addr = 0x00;
	uint8_t digit0_reg_addr = 0x01;
	uint8_t digit1_reg_addr = 0x02;
	uint8_t digit2_reg_addr = 0x03;
	uint8_t digit3_reg_addr = 0x04;
	uint8_t digit4_reg_addr = 0x05;
	uint8_t digit5_reg_addr = 0x06;
	uint8_t digit6_reg_addr = 0x07;
	uint8_t digit7_reg_addr = 0x08;
	uint8_t decodeMode_reg_addr = 0x09;
	uint8_t intensity_reg_addr = 0x0a;
	uint8_t scanLimit_reg_addr = 0x0b;
	uint8_t shutdown_reg_addr = 0x0c;
	uint8_t displayTest_reg_addr = 0x0f;
	uint8_t decodeMode_reg_config = 0x00;
	uint8_t intensity_reg_config = 0x02;
	uint8_t scanLimit_reg_config = 0x07;
	uint8_t shutdown_reg_config = 0x01;
	uint8_t displayTest_reg_config = 0x00;

    uint8_t buffer[8];
  	SPI_HandleTypeDef *hspi;

};

#endif
