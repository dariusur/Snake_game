# Snake_game
Classic snake game for Arduino and STM32 microcontrollers (Fig. 1). The project uses an 8x8 LED matrix for display and a graphical user interface (GUI) written in Python 3 for controls. The GUI runs on a PC and the commands are sent via USB cable to the microcontroller.

<div align="center">
  <img src="https://github.com/dariusur/Snake_game/blob/main/Snake_game.gif">
  <img src="https://github.com/dariusur/Snake_game/blob/main/Snake_game_GUI.png">
</div>
<div align="center">
  <i>Fig. 1. On the left: snake game running on Arduino Nano (inside). On the right: Python GUI for snake movement commands</i>
</div>

# Description
- Snake game is written in C++. A single class contains all variables and functions. Each function is responsible for a particular thing, e.g., snake movement, placement of fruit, collision checking, etc. The game evolves by looping through the functions in the correct order.
- The code for the snake game is contained within two files: Snake_game.h and Snake_game.cpp. These files can be found in **Arduino > lib > Snake_game**, as well as in **STM32 > Snake > Core > Inc/Src folders**.
- The code for Arduino and STM32 is mostly the same except for UART and SPI protocol implementations and a few other functions.
- The GUI script was programmed in Python using the tkinter framework from the standard Python library. The script binds the arrow keys on the keyboard to the movement commands of the snake. Serial communication via USB is used to send the commands to the microcontroller.
- Microcontroller processes the received commands and determines how the snake should move in the next frame. The frame buffer is then updated and later displayed on the LED matrix.
- The LED matrix is controlled by the microcontroller using SPI.

# Installation
## GUI
To run the GUI script you will need to install Python 3 (3.11.4 was used in particular). The script uses two libraries: tkinter and pyserial. If you have Python 3 and pyserial installed, you could just try running the script and it might work (you don't need to install tkinter because it's part of the standard Python library). If this doesn't work, then you should create a virtual environment and install all the libraries listed in **requirements.txt** (*pip install -r requirements.txt*) before launching the script.
When you launch the script, a command prompt will open and ask you to enter the COM port to which the microcontroller is connected to. After entering the number the GUI should show up on the screen.

## Arduino
### PlatformIO
Arduino folder is a PlatformIO project folder, so you can just simply open it by picking a folder in PlatformIO. Don't forget to set the development board in platformio.ini file before uploading the code.

## STM32
### STM32CubeIDE
**STM32 > Snake** is a STM32CbeIDE project folder. The code was tested on STM32 NUCLEO-F446RE development board. If you have the same board, you could try to simply open the project folder in STM32CubeIDE, and then upload the code to the board. For other boards, you will need to create a project from scratch and place the MAX7219.h, MAX7219.cpp, Snake_game.h, Snake_game.cpp into the new project. In main.cpp you should then add the code shown below. Afterwards you should be able to run the code.
```cpp
#include <Snake_game.h>
Snake snake(&hspi1, &huart2);
int main(void){
	uint16_t screen_refresh_period = 200;
	uint8_t LED_intensity = 6;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);
	snake.init(screen_refresh_period, LED_intensity, HAL_ADC_GetValue(&hadc1));
	HAL_ADC_Stop(&hadc1);
  	while (1){
		snake.play();
  	}
}
```

# Dependencies
Snake_game uses [MAX7219_library](https://github.com/dariusur/MAX7219_library) to control the LED matrix which is already included into the project folders for both the STM32 and Arduino.

