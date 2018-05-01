#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
#include "../libc/staticp.h"
int debug =0;

void kernel_main() {
    setcolor('4');
    clear_screen();

    //Manually Display Boot Sequence
    print_wait(); 
    kprint("Loading from disk..."); 

    print_wait(); 
    kprint("\nNo disk found...");  

    print_wait(); 
    kprint("\nLoading from external media...");        
    
    print_wait();
    kprint("\nNo suitable media found...");        
     
    print_wait(); 
    kprint("\nSystem will attempt to load into memory...");
    
    print_wait(); 
    kprint("\nStarting in 16bit real mode");

    print_wait(); 
    kprint("\nLoading Kernel into memory...");

    print_wait(); 
    kprint("\nKernal loaded");

    print_wait(); 
    kprint("\nLanded in 32bit protected mode");


    //Call ISR & IQRS    
    isr_install();
    irq_install();

    //  asm("int $2");
    //  asm("int $3");
    print_wait(); 
    kprint("\nBooting in 3"); 

    print_wait(); 
    kprint("\nBooting in 2"); 

    print_wait(); 
    kprint("\nBooting in 1");  

    print_wait(); 
    clear_screen();       
    
    kprint("blazeos$ ");        
    
}

void wait (){
    int i = 0, j = 0;
    for(i;i<2500000;i++){
        for(j;j<200000000*4;j++){

        }
    } 
}


void user_input(char *input) {
    if (strcmp(input, "SHUTDOWN") == 0) {
        // kprint("Stopping the CPU. Bye!\n");
        print_credits();
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        /* Lesson 22: Code to test kmalloc, the rest is unchanged */
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\nblazeos$ ");
    }else if (strcmp(input, "CLEAR") == 0) {
        clear_screen();
        kprint("blazeos$ ");        
    }else if (strcmp(input, "ABOUT") == 0) {
        print_about();  
        kprint("\nblazeos$ ");              
    }else if (strcmp(input, "HELP") == 0) {
        print_help();  
        kprint("\nblazeos$ ");                
    }else if (strcmp(input, "CREDITS") == 0) {
        print_credits();  
        kprint("\nblazeos$ ");               
    }else if (strcmp(input, "LOGO") == 0) {
        print_logo();  
        kprint("\nblazeos$ ");               
    }else if (strcmp(input, "SOURCES") == 0) {
        print_sources();  
        kprint("\nblazeos$ ");               
    }else if (strcmp(input, "TEST") == 0) {
        kprint("\n---Before Test---");        
            // wait();
            print_logo();
        kprint("\n---After Test---\nblazeos$ ");        
    }else if (strcmp(input, "DEBUG") == 0){
        if(debug==1){
            debug=0;
            kprint("Debugging is toggled off");            
        }else if(debug==0){
            debug=1;
            kprint("Debugging is toggled on");
        }

        kprint("\nblazeos$ ");
    
    }else if (strstw(input, "SET") == 0){
        char* split = substr(input, 4, strlen(input));


        if (strstw(split, "COLOR") == 0){
            char* split2 = substr(split, 6, strlen(split));

            if (strcmp(split2, "LGREEN") == 0){
                setcolor('a');
                clear_screen();
            }else if (strcmp(split2, "TEAL") == 0){
                setcolor('b');
                clear_screen();
            }else if (strcmp(split2, "ORANGE") == 0){
                setcolor('c');
                clear_screen();
            }else if (strcmp(split2, "PINK") == 0){
                setcolor('d');
                clear_screen();
            }else if (strcmp(split2, "YELLOW") == 0){
                setcolor('e');
                clear_screen();
            }else if (strcmp(split2, "WHITE") == 0){
                setcolor('f');
                clear_screen();
            }else if (strcmp(split2, "BLUE") == 0){
                setcolor('1');
                clear_screen();
            }else if (strcmp(split2, "GREEN") == 0){
                setcolor('2');
                clear_screen();
            }else if (strcmp(split2, "CYAN") == 0){
                setcolor('3');
                clear_screen();
            }else if (strcmp(split2, "RED") == 0){
                setcolor('4');
                clear_screen();
            }else if (strcmp(split2, "PURPLE") == 0){
                setcolor('5');
                clear_screen();
            }else if (strcmp(split2, "BROWN") == 0){
                setcolor('6');
                clear_screen();
            }else if (strcmp(split2, "LGREY") == 0){
                setcolor('7');
                clear_screen();
            }else if (strcmp(split2, "GREY") == 0){
                setcolor('8');
                clear_screen();
            }else if (strcmp(split2, "LBLUE") == 0){
                setcolor('9');
                clear_screen();
            }else if (strcmp(split2, "BLACK") == 0){
                setcolor('0');
                clear_screen();
            }
            if (strcmp(split2, "BLAZE") == 0){
                setcolor('g');
                clear_screen();
            }
            

            
        }

        kprint("blazeos$ ");
    
    }else if (debug == 1){
        kprint("You entered: ");
        kprint(input);
        kprint("\nblazeos$ ");
        
    
    }else{
        kprint("blazeos$ ");
    }
}
