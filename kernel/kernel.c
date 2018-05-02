#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
#include "../libc/staticp.h"

int debug =0;

void kernel_main() {

    //Manually Set Color TODO: Result of bug
    setcolor('4');
    clear_screen();

    //Manually Display Boot Sequence
    print_wait(); 
    blazePrint("Loading from disk..."); 

    print_wait(); 
    blazePrint("\nNo disk found...");  

    print_wait(); 
    blazePrint("\nLoading from external media...");        
    
    print_wait();
    blazePrint("\nNo suitable media found...");        
     
    print_wait(); 
    blazePrint("\nSystem will attempt to load into memory...");
    
    print_wait(); 
    blazePrint("\nStarting in 16bit real mode");

    print_wait(); 
    blazePrint("\nLoading Kernel into memory...");

    print_wait(); 
    blazePrint("\nKernal loaded");

    print_wait(); 
    blazePrint("\nLanded in 32bit protected mode");


    //Call ISR & IQRS    
    isr_install();
    irq_install();

    print_wait(); 
    blazePrint("\nBooting in 3"); 

    print_wait(); 
    blazePrint("\nBooting in 2"); 

    print_wait(); 
    blazePrint("\nBooting in 1");  

    print_wait(); 
    clear_screen();       
    
    blazePrint("blazeos$ ");        
    
}

//long wait method needs rewriting outside of a loop
void wait (){
    int i = 0, j = 0;
    for(i;i<2500000;i++){
        for(j;j<200000000*4;j++){

        }
    } 
}

//Handle User Input | Commands
void user_input(char *input) {
    if (strcmp(input, "SHUTDOWN") == 0) {
        print_credits();
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        blazePrint("Page: ");
        blazePrint(page_str);
        blazePrint(", physical address: ");
        blazePrint(phys_str);
        blazePrint("\nblazeos$ ");
    }else if (strcmp(input, "CLEAR") == 0) {
        clear_screen();
        blazePrint("blazeos$ ");        
    }else if (strcmp(input, "ABOUT") == 0) {
        print_about();  
        blazePrint("\nblazeos$ ");              
    }else if (strcmp(input, "HELP") == 0) {
        print_help();  
        blazePrint("\nblazeos$ ");                
    }else if (strcmp(input, "CREDITS") == 0) {
        print_credits();  
        blazePrint("\nblazeos$ ");               
    }else if (strcmp(input, "LOGO") == 0) {
        print_logo();  
        blazePrint("\nblazeos$ ");               
    }else if (strcmp(input, "SOURCES") == 0) {
        print_sources();  
        blazePrint("\nblazeos$ ");               
    }else if (strcmp(input, "TEST") == 0) {
        blazePrint("\n---Before Test---");        
            // wait();
            print_logo();
        blazePrint("\n---After Test---\nblazeos$ ");        
    }else if (strcmp(input, "DEBUG") == 0){
        if(debug==1){
            debug=0;
            blazePrint("Debugging is toggled off");            
        }else if(debug==0){
            debug=1;
            blazePrint("Debugging is toggled on");
        }

        blazePrint("\nblazeos$ ");
    
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

        blazePrint("blazeos$ ");
    
    }else if (debug == 1){
        blazePrint("You entered: ");
        blazePrint(input);
        blazePrint("\nblazeos$ ");
        
    
    }else{
        blazePrint("blazeos$ ");
    }
}
