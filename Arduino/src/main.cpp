#include "Snake_game.h"

const uint8_t DIN = 5, CS = 6, CLK = 7;
const uint16_t SCREEN_REFRESH_PERIOD = 200;
const uint8_t LED_INTENSITY = 7; // 0 - 15

Snake snake(DIN, CS, CLK);

void setup() {
  snake.init(SCREEN_REFRESH_PERIOD, LED_INTENSITY);
}

void loop() {
  snake.play();
}