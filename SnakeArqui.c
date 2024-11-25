#include "ripes_system.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_SNAKE_LENGTH 100

int eaten = 0;
unsigned int apple_x = 0;
unsigned int apple_y = 0;
unsigned int length = 2;
unsigned int snake[MAX_SNAKE_LENGTH][2]; // Array for snake segments

void set_pixel(unsigned int x, unsigned int y, unsigned int color) {
    unsigned int *led_base = LED_MATRIX_0_BASE;
    unsigned int offset = x + (24 - y) * LED_MATRIX_0_WIDTH;
    unsigned int *address = led_base + offset;
    *address = color;
}

void create_apple(unsigned int x, unsigned int y) {
    set_pixel(x, y, 0x00FF00);
    set_pixel(x + 1, y, 0x00FF00);
    set_pixel(x, y + 1, 0x00FF00);
    set_pixel(x + 1, y + 1, 0x00FF00);
}

void set_apple() {
    apple_x = rand() % 34; // Random position within the LED matrix
    apple_y = rand() % 24;
    create_apple(apple_x, apple_y);
}

int collision_apple(unsigned int next_x, unsigned int next_y) {
    return (next_x == apple_x && next_y == apple_y);
}

void init_snake(unsigned int x, unsigned int y, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        snake[i][0] = x - i; // Snake starts horizontally to the left
        snake[i][1] = y;
        set_pixel(snake[i][0], snake[i][1], 0xFF0000);
    }
}

void move_snake(unsigned int next_x, unsigned int next_y) {
    // Clear the tail
    set_pixel(snake[length - 1][0], snake[length - 1][1], 0x000000);

    // Shift body segments
    for (int i = length - 1; i > 0; i--) {
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }

    // Update the head position
    snake[0][0] = next_x;
    snake[0][1] = next_y;

    // Redraw the snake
    for (int i = 0; i < length; i++) {
        set_pixel(snake[i][0], snake[i][1], 0xFF0000);
    }
}

int main() {
    unsigned int *up = D_PAD_0_UP;
    unsigned int *right = D_PAD_0_RIGHT;
    unsigned int *down = D_PAD_0_DOWN;
    unsigned int *left = D_PAD_0_LEFT;

    unsigned int x = 17; // Initial x position of the snake's head
    unsigned int y = 12; // Initial y position of the snake's head

    unsigned int key_up_pressed = 0;
    unsigned int key_right_pressed = 0;
    unsigned int key_down_pressed = 0;
    unsigned int key_left_pressed = 0;

    // Initialize the snake and place the first apple
    init_snake(x, y, length);
    set_apple();

    int bandera_juego = 1;

    while (bandera_juego) {
        // Handle input and update position
        if (*up == 1 && key_up_pressed == 0) {
            key_up_pressed = 1;
            y++;
        } else if (*down == 1 && key_down_pressed == 0) {
            key_down_pressed = 1;
            y--;
        } else if (*left == 1 && key_left_pressed == 0) {
            key_left_pressed = 1;
            x--;
        } else if (*right == 1 && key_right_pressed == 0) {
            key_right_pressed = 1;
            x++;
        }

        // Handle key release
        key_up_pressed = (*up == 0) ? 0 : key_up_pressed;
        key_down_pressed = (*down == 0) ? 0 : key_down_pressed;
        key_left_pressed = (*left == 0) ? 0 : key_left_pressed;
        key_right_pressed = (*right == 0) ? 0 : key_right_pressed;

        // Check wall collision
        if (x >= 34 || x < 0 || y >= 24 || y < 0) {
            printf("Game Over: Snake hit the wall\n");
            bandera_juego = 0;
            break;
        }

        // Move the snake
        move_snake(x, y);

        // Check for apple collision
        if (collision_apple(x, y)) {
            length++; // Increase snake length
            eaten = 0; // Mark apple as eaten
        }

        // If no apple is on the board, generate a new one
        if (eaten == 0) {
            set_apple();
            eaten = 1;
        }
    }

    return 0;
}
