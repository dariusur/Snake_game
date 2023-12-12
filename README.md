# Snake_game
Classic snake game for Arduino and STM32 microcontrollers (Fig. 1). The project uses an 8x8 LED matrix for display and a graphical user interface (GUI) written in Python 3 for controls. The GUI runs on a PC and the commands are sent via USB cable to the microcontroller.
<br></br>
<p align="left">
  <img src="https://github.com/dariusur/Snake_game/blob/main/Snake_game.gif">
</p>
<p align="left">
  <i>Fig. 1. Snake game running on Arduino Nano (inside)</i>
</p>

# Overview
- The code for the snake game is contained within two files: Snake_game.h and Snake_game.cpp. These files can be found in **Arduino > lib > Snake_game**, as well as in **STM32 > Snake > Core > Inc/Src folders**.
- The code for Arduino and STM32 is mostly the same except for UART and SPI protocol implementations.
- The GUI script was programmed in Python using tkinter framework from the standard Python library. The script binds the arrow keys on the keyboard to movement commands of the snake. Serial communication via USB is used to send the commands to the microcontroller.
- 

# Installation
TODO

# Dependencies
Snake_game uses [MAX7219_library](https://github.com/dariusur/MAX7219_library) to control the LED matrix which is already included into the project folders for both the STM32 and Arduino.

