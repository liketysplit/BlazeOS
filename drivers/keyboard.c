#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include <stdint.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A
#define RSHIFT 0xAA
#define SC_MAX 57

static char key_buffer[256];
int shiftPressed = 0;


const char *sc_name[] = {   "ERROR", "Esc", "1", "2", "3", "4", "5", "6", "7", "8", 
                            "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", "R", 
                            "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
                            "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", 
                            "'", "`", "LShift", "\\", "Z", "X", "C", "V", "B", "N", 
                            "M", ",", ".", "/", "RShift", "Keypad *", "LAlt", "Spacebar"}; //8

const char sc_ascii[] = {   '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', 
                            '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r',
                            't', 'y', 'u', 'i', 'o', 'p', '[', ']', '?', '?', 
                            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 
                            '\'', '`', 'LSHIFT', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 
                            'm', ',', '.', '/', 'RSHIFT', '?', '?', ' '}; //8

const char sc_asciii[] = {   '?', '?', '!', '@', '#', '$', '%', '^', '&', '*', 
                            '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R',
                            'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '?', '?', 
                            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 
                            '\"', '~', 'LSHIFT', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 
                            'M', '<', '>', '?', 'RSHIFT', '?', '?', ' '}; //8

static void keyboard_callback(registers_t *regs) {

    //Data from the PiC
    uint8_t scancode = port_byte_in(0x60);
    
    //Shift
    if(scancode == 170 || scancode == 182){
        shiftPressed = 0;
    }

    //Ignore Cases
    if (scancode > SC_MAX) return;

    //Backspace
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        blazePrint_backspace();

    //Enter
    } else if (scancode == ENTER) {
        blazePrint("\n");
        user_input(key_buffer); //Send User input to Kernel
        key_buffer[0] = '\0'; //Clear the Buffer
    }else if (scancode == 0x2A || scancode == 0x36) {
        shiftPressed = 1;
    } else {
        char letter;
        if(shiftPressed==1){
            letter = sc_asciii[(int)scancode];
        }else{
            letter = sc_ascii[(int)scancode];
        }

        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        blazePrint(str);
        
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
