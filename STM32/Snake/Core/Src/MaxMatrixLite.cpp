/*
 * This is a lite version of the MaxMatrix library
 * written specifically for the Snake game on STM32 microcontroller.
 * Code adapted from https://github.com/riyas-org/max7219
 */

#include "MaxMatrixLite.h"

MaxMatrix::MaxMatrix(SPI_HandleTypeDef *hspi_arg)
{
	hspi = hspi_arg;
	for (int i=0; i<8; i++){
		buffer[i] = 0;
	}
}

void MaxMatrix::init()
{
	sendData(&decodeMode_reg_addr, &decodeMode_reg_config); // No decode for digits 7-0
	sendData(&intensity_reg_addr, &intensity_reg_config); // 0x00 - 0x0F
	sendData(&scanLimit_reg_addr, &scanLimit_reg_config); // display all digits
	sendData(&shutdown_reg_addr, &shutdown_reg_config); // normal operation
	sendData(&displayTest_reg_addr, &displayTest_reg_config); // normal operation
	clear(); // Turn all LEDs off
}

void MaxMatrix::setIntensity(uint8_t *intensity)
{
	sendData(&intensity_reg_addr, intensity);
}

void MaxMatrix::clear()
{
	for (uint8_t i=1; i<=8; i++){
		buffer[i] = 0;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_SPI_Transmit(hspi, &i, 1, 100);
		HAL_SPI_Transmit(hspi, &(buffer[i-1]), 1, 100);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	}		
}

void MaxMatrix::sendData(uint8_t *reg_addr, uint8_t *data)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, reg_addr, 1, 100);
	HAL_SPI_Transmit(hspi, data, 1, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}

void MaxMatrix::setDot(uint8_t col, uint8_t row, uint8_t value)
{
	uint8_t col_temp = col + 1; // digit addresses start at 0x01
	switch(value){
	case 0:
		buffer[col_temp] &= ~(1<<row);
		break;
	case 1:
		buffer[col_temp] |= 1<<row;
		break;
	default: return;
	}
    sendData(&col_temp, &buffer[col_temp]);
}
