#include <Snake_game.h>

Snake::Snake(SPI_HandleTypeDef *hspi_arg, UART_HandleTypeDef *huart_arg) : matrix(hspi_arg){
	huart = huart_arg;
};

void Snake::init(uint16_t screen_refresh_period_arg, uint8_t LED_intensity, uint16_t rand_number){
    matrix.init();
    matrix.sendData(intensity_reg_addr, LED_intensity); // configure intensity
    srand(rand_number); // use analogRead 0'th port to set the seed for random number generator
    screen_refresh_period = screen_refresh_period_arg; // 200 ms = 5 Hz
}

void Snake::play(){
    restart();
    while(true){
        receive_movement_command();
        move();
        if(check_for_collision() == 1) break;        
        place_fruit();
        draw();
        HAL_Delay(screen_refresh_period);
    }
    game_over();
}
// Place snake, on restart the snake is 3 dots long and moves left
void Snake::restart(){
    snake_len = 3;
    x_velocity = -1; // move left
    y_velocity = 0;
    fruit_exists = 0;
    // place snake
    for(int i=0;i<snake_len;i++){
		x_coord_snake[i] = i+4;
        y_coord_snake[i] = 4;
    }
    place_fruit();
    draw();
}
void Snake::draw(){
    matrix.clear();
    matrix.switchLED(x_coord_fruit, y_coord_fruit, 1); // draw fruit
    for(int i=0;i<snake_len;i++){
        matrix.switchLED(x_coord_snake[i], y_coord_snake[i], 1); // draw snake
    }
}
void Snake::place_fruit(){
    while(fruit_exists == 0){
        fruit_exists = 1;
        x_coord_fruit = rand() % 8; // generate a random number with value ranging from 0 to 7
        y_coord_fruit = rand() % 8;
        for(int i=0;i<snake_len;i++){
            if((x_coord_snake[i] == x_coord_fruit) && (y_coord_snake[i] == y_coord_fruit)){
                fruit_exists = 0;
                break;
            }
        }
    }
}

uint8_t Snake::receive_movement_command(){
    uint8_t serial_data_in;
    uint8_t ret_value = HAL_UART_Receive(huart, &serial_data_in, 1, 10);
	if (ret_value == HAL_OK){
        // set snake movement direction
        switch(serial_data_in){
            case '0': // move up
                if(y_velocity != 1){ // restrict motion in the opposite direction
                    x_velocity = 0; // (-1) - left, 0 - no motion, 1 - right
                    y_velocity = -1; // (-1) - up, 0 - no motion, 1 - down
                }
                break;
            case '1': // move down
                if(y_velocity != -1){
                    x_velocity = 0;
                    y_velocity = 1;
                }
                break;
            case '2': // move left
                if(x_velocity != 1){
                    x_velocity = -1;
                    y_velocity = 0;
                }
                break;
            case '3': // move down
                if(x_velocity != -1){
                    x_velocity = 1;
                    y_velocity = 0;
                }
                break;
            default : break;
        }
        return 0; // snake moved
    }
    return 1; // snake didn't move
}
void Snake::move(){
    // record tail position, this is used to know where to grow the snake if it eats a fruit
    x_coord_snake_tail = x_coord_snake[snake_len-1];
    y_coord_snake_tail = y_coord_snake[snake_len-1];
    // shift coordinates from back to front of the array
    for(int i=(snake_len-1);i>0;i--){
        x_coord_snake[i] = x_coord_snake[i-1];
        y_coord_snake[i] = y_coord_snake[i-1];
    }
    // move the head of the snake
    x_coord_snake[0] += x_velocity;
    y_coord_snake[0] += y_velocity;
    // check if snake is out of bounds
    if(x_coord_snake[0] < 0){
		x_coord_snake[0] = 7;
    }
    else if(x_coord_snake[0] > 7){
		x_coord_snake[0] = 0;
    }
    else if(y_coord_snake[0] < 0){
		y_coord_snake[0] = 7;
    }
    else if(y_coord_snake[0] > 7){
		y_coord_snake[0] = 0;
	}
}
uint8_t Snake::check_for_collision(){
    // snake can only eat itself if snake_len > 4
    for(int i=4;i<snake_len;i++){
        if((x_coord_snake[0] == x_coord_snake[i]) && (y_coord_snake[0] == y_coord_snake[i])){
            return 1; // snake eats itself = game over
        }
    }
    if((x_coord_snake[0] == x_coord_fruit) && (y_coord_snake[0] == y_coord_fruit)){
        fruit_exists = 0; // snake eats fruit
        x_coord_snake[snake_len] = x_coord_snake_tail;
        y_coord_snake[snake_len] = y_coord_snake_tail;
        snake_len++; // snake grows
        return 2; // snake eats fruit = snake grows
    }
    return 0; // no collision = continue
}

void Snake::game_over(){
    matrix.clear();
    for(int i=0;i<snake_len;i++){
        uint8_t column = i / 8;
        uint8_t row = i % 8;
        matrix.switchLED(column,row,1);
    }
    while(receive_movement_command() == 1); // wait for any input from user to restart the game
}
