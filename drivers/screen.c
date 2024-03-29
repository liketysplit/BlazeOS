#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include <stdint.h>

int get_cursor_balance();
void set_cursor_balance(int offset);
int print_char(char c, int col, int row, char attr);
int get_balance(int col, int row);
int get_balance_row(int offset);
int get_balance_col(int offset);

char colorhex = RED_ON_WHITE;

void blazePrint_at(char *message, int col, int row) {
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_balance(col, row);
    else {
        offset = get_cursor_balance();
        row = get_balance_row(offset);
        col = get_balance_col(offset);
    }

    int i = 0;
    char* temp;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, colorhex );
        row = get_balance_row(offset);
        col = get_balance_col(offset);
    }
}

void blazePrint(char *message) {
    blazePrint_at(message, -1, -1);
}

void blazePrint_backspace() {
    if(get_balance_col(get_cursor_balance()-2)>8){
    int offset = get_cursor_balance()-2;
    int row = get_balance_row(offset);
    int col = get_balance_col(offset);
    print_char(0x08, col, row, colorhex);
    }
}

void system_backspace() {
    int offset = get_cursor_balance()-2;
    int row = get_balance_row(offset);
    int col = get_balance_col(offset);
    print_char(0x08, col, row, colorhex);
    
}

void setcolor( char i ){
    switch(i){
        case 'a':{ colorhex =  Light_Green_ON_BLACK;break;}
        case 'b':{ colorhex =  Teal_ON_BLACK;break;}
        case 'c':{ colorhex =  Orange_ON_WHITE;break;}
        case 'd':{ colorhex =  Pink_ON_WHITE;break;}
        case 'e':{ colorhex =  Yellow_ON_BLACK;break;}
        case 'f':{ colorhex =  WHITE_ON_BLACK;break;}
        case 'g':{ colorhex =  G;break;}

        case '1':{ colorhex =  Dark_Blue_ON_WHITE;break;}
        case '2':{ colorhex =  Dark_Green_ON_WHITE;break;}
        case '3':{ colorhex =  Cyan_ON_WHITE;break;}
        case '4':{ colorhex =  RED_ON_WHITE;break;}
        case '5':{ colorhex =  Purple_ON_BLACK;break;}
        case '6':{ colorhex =  Brown_ON_WHITE;break;}
        case '7':{ colorhex =  Light_Grey_ON_BLACK;break;}
        case '8':{ colorhex =  Dark_Grey_ON_WHITE;break;}
        case '9':{ colorhex =  Light_BLue_ON_BLACK;break;}
        case '0':{ colorhex =  Black_ON_WHITE;break;}

        
    }
}

int print_char(char c, int col, int row, char attr) {
    uint8_t *vidmem = (uint8_t*) VIDEO_ADDRESS;
    if (!attr) attr = colorhex;

    //Errors
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_balance(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_balance(col, row);
    else offset = get_cursor_balance();

    if (c == '\n') {
        row = get_balance_row(offset);
        offset = get_balance(0, row+1);
    //Backspace
    } else if (c == 0x08) { 
        vidmem[offset] = ' ';
        vidmem[offset+1] = attr;
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    //Scroll
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memory_copy((uint8_t*)(get_balance(0, i) + VIDEO_ADDRESS),
                        (uint8_t*)(get_balance(0, i-1) + VIDEO_ADDRESS),
                        MAX_COLS * 2);

        
    //TODO: Fix the issue where when you get to a new line, and type to the end of line it remembers the last character as well as system_backspace should be used because you can't delete anything before col 9
        char *last_line = (char*) (get_balance(0, MAX_ROWS-1) + (uint8_t*) VIDEO_ADDRESS);
        for (i = 0; i < MAX_COLS; i++){
            system_backspace();
        }
            

        offset -= 2 * MAX_COLS;
    }

    set_cursor_balance(offset);
    return offset;
}

int get_cursor_balance() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_balance(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    uint8_t *screen = (uint8_t*) VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = colorhex;
    }
    set_cursor_balance(get_balance(0, 0));
}

int get_balance(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_balance_row(int offset) { return offset / (2 * MAX_COLS); }
int get_balance_col(int offset) { return (offset - (get_balance_row(offset)*2*MAX_COLS))/2; }
