#include <MAX7219.h>

MAX7219::MAX7219(SPI_HandleTypeDef *hspi_arg)
{
	hspi = hspi_arg;
}

void MAX7219::init()
{
	sendData(decodeMode_reg_addr, decodeMode_reg_config);
	sendData(intensity_reg_addr, intensity_reg_config);
	sendData(scanLimit_reg_addr, scanLimit_reg_config);
	sendData(shutdown_reg_addr, shutdown_reg_config);
	sendData(displayTest_reg_addr, displayTest_reg_config);
	clear(); // Turn all LEDs off
}

void MAX7219::clear()
{
	for (uint8_t i=1; i<=8; i++){
		buffer[i-1] = 0;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_SPI_Transmit(hspi, &i, 1, 100);
		HAL_SPI_Transmit(hspi, &buffer[i-1], 1, 100);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	}
}

void MAX7219::sendData(uint8_t reg_addr, uint8_t data)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, &reg_addr, 1, 100);
	HAL_SPI_Transmit(hspi, &data, 1, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}

void MAX7219::switchLED(uint8_t col, uint8_t row, uint8_t value)
{
	//uint8_t col_temp = col + 1; // digit addresses start at 0x01
	switch(value){
	case 0:
		buffer[col] &= ~(1<<row);
		break;
	case 1:
		buffer[col] |= 1<<row;
		break;
	default: return;
	}
    sendData(col+1, buffer[col]);
}
