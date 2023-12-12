# Snake_game
Classic snake game for Arduino and STM32 microcontrollers (Fig. 1). The project uses an 8x8 LED matrix for display and a graphical user interface (GUI) written in Python 3 for controls. The GUI runs on a PC and the commands are sent via USB cable to the microcontroller.
<br></br>
<p align="left">
  <img src="https://github.com/dariusur/Snake_game/blob/main/Snake_game.gif">
</p>
<p align="left">
  <i>Fig. 1. Snake game running on Arduino Nano (inside)</i>
</p>

# Description
- Snake game is written in C++. A single class contains all variables and functions. Each function is responsible for a particular thing, e.g., snake movement, placement of fruit, collision checking, etc. The game evolves by looping through the functions in the correct order.
- The code for the snake game is contained within two files: Snake_game.h and Snake_game.cpp. These files can be found in **Arduino > lib > Snake_game**, as well as in **STM32 > Snake > Core > Inc/Src folders**.
- The code for Arduino and STM32 is mostly the same except for UART and SPI protocol implementations and a few other functions.
- The GUI script was programmed in Python using tkinter framework from the standard Python library. The script binds the arrow keys on the keyboard to movement commands of the snake. Serial communication via USB is used to send the commands to the microcontroller.
- Microcontroller processes the received commands and determines how the snake should move in the next frame. The frame buffer is then updated and later displayed on the LED matrix.
- The LED matrix is controlled by the microcontroller using SPI.

# Installation
## GUI
To run the GUI script you will need to install Python 3 (3.11.4 was used in particular). The script uses two libraries: tkinter and pyserial. If you have Python 3 and pyserial installed, you could just try running the script and it might work (you don't need to install tkinter because it's part of the standard Python library). If this doesn't work, then you should create a virtual environment and install all the libraries listed in **requirements.txt** (*pip install -r requirements.txt*) before launching the script.
When you launch the script, a command prompt will open and ask you to enter the COM port to which the microcontroller is connected to. After entering the number the GUI should show up on the screen.

##

# Dependencies
Snake_game uses [MAX7219_library](https://github.com/dariusur/MAX7219_library) to control the LED matrix which is already included into the project folders for both the STM32 and Arduino.

