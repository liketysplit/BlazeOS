#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include <stdint.h>

/* Declaration of private functions */
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

char colorhex = 0x0f;

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void kprint_at(char *message, int col, int row) {
    /* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    char* temp;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, colorhex );
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

void kprint_backspace() {
    if(get_offset_col(get_cursor_offset()-2)>8){
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, colorhex);
    }
}

void system_backspace() {
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, colorhex);
    
}

void setcolor( char i ){
    switch(i){
        case 'a':{ colorhex =  Light_Green_ON_BLACK;break;}
        case 'b':{ colorhex =  Teal_ON_BLACK;break;}
        case 'c':{ colorhex =  Orange_ON_WHITE;break;}
        case 'd':{ colorhex =  Pink_ON_WHITE;break;}
        case 'e':{ colorhex =  Yellow_ON_BLACK;break;}
        case 'f':{ colorhex =  White_ON_BLACK;break;}
        case 'g':{ colorhex =  G;break;}

        case '1':{ colorhex =  Dark_Blue_ON_WHITE;break;}
        case '2':{ colorhex =  Dark_Green_ON_WHITE;break;}
        case '3':{ colorhex =  Cyan_ON_WHITE;break;}
        case '4':{ colorhex =  Red_ON_WHITE;break;}
        case '5':{ colorhex =  Purple_ON_BLACK;break;}
        case '6':{ colorhex =  Brown_ON_WHITE;break;}
        case '7':{ colorhex =  Light_Grey_ON_BLACK;break;}
        case '8':{ colorhex =  Dark_Grey_ON_WHITE;break;}
        case '9':{ colorhex =  Light_BLue_ON_BLACK;break;}
        case '0':{ colorhex =  Black_ON_WHITE;break;}

        
    }
}


/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * Innermost print function for our kernel, directly accesses the video memory 
 *
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */
int print_char(char c, int col, int row, char attr) {
    uint8_t *vidmem = (uint8_t*) VIDEO_ADDRESS;
    if (!attr) attr = colorhex;

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else if (c == 0x08) { /* Backspace */
        vidmem[offset] = ' ';
        vidmem[offset+1] = attr;
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memory_copy((uint8_t*)(get_offset(0, i) + VIDEO_ADDRESS),
                        (uint8_t*)(get_offset(0, i-1) + VIDEO_ADDRESS),
                        MAX_COLS * 2);

        /* Blank last line */
        //TODO: Fix the issue where when you get to a new line, and type to the end of line it remembers the last character as well as system_backspace should be used because you can't delete anything before col 9
        char *last_line = (char*) (get_offset(0, MAX_ROWS-1) + (uint8_t*) VIDEO_ADDRESS);
        for (i = 0; i < MAX_COLS; i++){
            system_backspace();
            //print_char(0x08, i, MAX_ROWS-2, colorhex);
            //  vidmem[i] = 0;
            //  vidmem[i+1] = colorhex;
            //last_line[i] = 0;
        }
            

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
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
    set_cursor_offset(get_offset(0, 0));
}

// void print_logo(){
    
//     kprint("\n              ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___");print_wait();
//     kprint("\n ");
//     kprint("\n                     (                   )              )    (   ");print_wait();
//     kprint("\n                (    )\\ )     (       ( /(           ( /(    )\\ )  ");print_wait();
//     kprint("\n              ( )\\  (()/(     )\\      )\\())  (       )\\())  (()/(  ");print_wait();
//     kprint("\n              )((_)  /(_)) ((((_)(   ((_)\\   )\\     ((_)\\    /(_)) ");print_wait();
//     kprint("\n             ((_)_  (_))    )\\ _ )\\   _((_) ((_)      ((_)  (_))   ");print_wait();
//     kprint("\n              | _ ) | |     (_)_\\(_) |_  /  | __|    / _ \\  / __| ");print_wait();
//     kprint("\n              | _ \\ | |__    / _ \\    / /   | _|    | (_) | \\__ \\  ");print_wait();
//     kprint("\n              |___/ |____|  /_/ \\_\\  /___|  |___|    \\___/  |___/  ");print_wait();
//     kprint("\n  ");                                               
//     kprint("\n              ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___");print_wait();

// }

// void print_about(){
//     kprint("        Name: BlazeOS");print_wait();
//     kprint("\n     Version: 0.0.0");print_wait();
//     kprint("\n     Authors: Tyler Angelier, Rick Boles, Michael Montgomery");print_wait();
//     kprint("\n    Compiler: i386elf-gcc");print_wait();
//     kprint("\nTechnologies: qemu, nasm, gmp, mpfr, libmpc, gcc-4.9, binutils");print_wait();
//     //TODO: get git link
//     kprint("\n      GitHub: https://github.com/liketysplit/");print_wait();
//     kprint("\n   Professor: Dr. Sudip Chakraborty");print_wait();
//     kprint("\n      Course: CS4345 Operating Systems Fall 2018");print_wait();
//     kprint("\nDate Started: Jan. 12th 2018");print_wait();
//     //TODO: Update date
//     kprint("\nDate Updated: April 23rd 2018");print_wait();
//     kprint("\n   Languages: Assembly, C");print_wait();
//     kprint("\n        Info: Paper on git.");print_wait();
// }

// void print_help(){
//     //TODO: As you add commands, please add them here as well
//     //TODO: Add a brief desc of each command
//     kprint("Functions Available:\n  ABOUT\n  CLEAR\n  CREDITS\n  DEBUG\n  HELP\n  PAGE\n  SET COLOR <COLORNAME>\n  SHUTDOWN\n  SOURCES\n  TEST");
// }

// void print_credits(){
//     kprint("\n");
//     print_logo();
//     wait();
//     kprint("\n"); kprint("\n"); kprint("\n");    
//     print_about();
//     wait();
//     kprint("\n"); kprint("\n"); kprint("\n");    
//     print_sources();
//     //TODO: Add Chakraborty's face to end of credits roll
//     // wait();
//     // kprint("\n");
    


// }

// void print_sources(){
//     //TODO: Consult with Micke to get a fine tuned list of sources
//     kprint(" OS Dev Wiki: https://forum.osdev.org/index.php");print_wait();
//     kprint("\nLow Level EU: http://lowlevel.eu/");print_wait();

// }


int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }

// void print_wait(){
//     int i = 0, j = 0;
//     for(i;i<1250000;i++){
//         for(j;j<100000000;j++){

//         }
//     } 
// }