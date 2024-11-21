#include "ripes_system.h"
#include "stdio.h"
#include "stdlib.h"


void set_pixel(unsigned int x, unsigned int y, unsigned int color) {
    unsigned int *led_base = LED_MATRIX_0_BASE; 
    unsigned int offset = x + (24 - y) * LED_MATRIX_0_WIDTH; 
    unsigned int *address = led_base + offset; 
    *address = color; 
}


void create_snake(unsigned int x, unsigned int y){
    set_pixel(x, y, 0xFF0000);
    set_pixel(x + 1, y, 0xFF0000);
    set_pixel(x, y + 1, 0xFF0000);
    set_pixel(x + 1, y + 1, 0xFF0000);

}

void create_apple(unsigned int x,unsigned int y){
    set_pixel(x,y,0x00FF00);
    set_pixel(x + 1,y,0x00FF00);
    set_pixel(x,y + 1,0x00FF00);
    set_pixel(x + 1,y + 1,0x00FF00);
}
    
void set_apple(){
    unsigned int rand_x = rand() % 32;
    unsigned int rand_y = rand() % 21;
    printf("%d %d",rand_x,rand_y);
    
    create_apple(rand_x,rand_y);
}
    
void move_snake(unsigned int x, unsigned int y){
        create_snake(x,y);
}

int main(){

    unsigned int *up = D_PAD_0_UP;
    unsigned int *right = D_PAD_0_RIGHT;
    unsigned int *down = D_PAD_0_DOWN;
    unsigned int *left = D_PAD_0_LEFT;
    
    unsigned int x = 17;
    unsigned int y = 12;
    
    unsigned int key_up_pressed = 0;
    unsigned int key_right_pressed = 0;
    unsigned int key_down_pressed = 0;
    unsigned int key_left_pressed = 0;
    
    create_snake(x,y);
    set_apple();
    
    int bandera_juego = 1;

    while(bandera_juego){
        
        if (x >= 33 || x < 0 || y >= 23 || y < 0) {
        printf("Game Over: Snake hit the wall\n");
        bandera_juego = 0;
        }

        if (*up == 1 && key_up_pressed == 0){
            key_up_pressed = 1;
            y += 1;
            move_snake(x,y);
        } else if (*down == 1 && key_down_pressed == 0){
            key_down_pressed = 1;
            y -= 1;
            move_snake(x,y);
        } else if (*left == 1 && key_left_pressed == 0){
            key_left_pressed = 1;
            x -= 1;
            move_snake(x,y);
            
        } else if (*right == 1 && key_right_pressed == 0){
            key_right_pressed = 1;
            x += 1;
            move_snake(x,y);
        }
        
        if (*up == 0){
            key_up_pressed = 0;
        }
        if (*down == 0){
            key_down_pressed = 0;
        }
        if (*left == 0){
            key_left_pressed = 0;
        }
        if (*right == 0){
            key_right_pressed = 0;
        }
        
    }
    return 0;
    }
    