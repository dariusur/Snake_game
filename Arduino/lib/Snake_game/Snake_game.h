#ifndef Snake_h
#define Snake_h

#include "Arduino.h"
#include "MAX7219.h"

class Snake{
	public:
		Snake(uint8_t din, uint8_t cs, uint8_t clk);
		void init(uint16_t screen_refresh_period_arg, uint8_t LED_intensity);
		void play();
	
	private:
		uint16_t screen_refresh_period; // time in ms
		int8_t x_coord_snake[64], y_coord_snake[64];
		int8_t x_coord_snake_tail, y_coord_snake_tail;
		int8_t x_velocity, y_velocity;
		uint8_t snake_len;
		uint8_t x_coord_fruit, y_coord_fruit;
		uint8_t fruit_exists;

		MAX7219 matrix;

		void restart();
		void place_fruit();
		uint8_t receive_movement_command();
		void move();
		uint8_t check_for_collision();
		void draw();
		void game_over(); // display score
};

#endif