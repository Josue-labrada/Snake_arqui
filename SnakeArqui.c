#include "ripes_system.h"
#include "stdio.h"


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
    set_pixel(0,24,0x00ff00);

    while(1){
        if (*up == 1 && key_up_pressed == 0){
            key_up_pressed = 1;
            y += 1;
            y = y % 24;
            move_snake(x,y);
        } else if (*down == 1 && key_down_pressed == 0){
            key_down_pressed = 1;
            y -= 1;
            if (y < 0){
                y = 24;
                printf("x: %d y:%d",x,y );
            }
            move_snake(x,y);
        } else if (*left == 1 && key_left_pressed == 0){
            key_left_pressed = 1;
            x -= 1;
            if (x < 0){
                x = 33;
                y -= 1;
                move_snake(x,y);
            }
            move_snake(x,y);
            
        } else if (*right == 1 && key_right_pressed == 0){
            key_right_pressed = 1;
            x += 1;
            x = x % 34;
            
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
    