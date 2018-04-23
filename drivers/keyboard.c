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


static char key_buffer[256];
int shiftPressed = 0;

#define SC_MAX 57
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
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    
    if(scancode == 170 || scancode == 182){
        shiftPressed = 0;
    }
    if (scancode > SC_MAX) return;

    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        kprint_backspace();
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    }else if (scancode == 0x2A || scancode == 0x36) {
        shiftPressed = 1;
    } else {
        char letter;
        if(shiftPressed==1){
            letter = sc_asciii[(int)scancode];
        }else{
            letter = sc_ascii[(int)scancode];
        }

        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
        
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
