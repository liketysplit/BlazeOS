void print_logo(){
    
    kprint("\n              ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___");print_wait();
    kprint("\n ");
    kprint("\n                     (                   )              )    (   ");print_wait();
    kprint("\n                (    )\\ )     (       ( /(           ( /(    )\\ )  ");print_wait();
    kprint("\n              ( )\\  (()/(     )\\      )\\())  (       )\\())  (()/(  ");print_wait();
    kprint("\n              )((_)  /(_)) ((((_)(   ((_)\\   )\\     ((_)\\    /(_)) ");print_wait();
    kprint("\n             ((_)_  (_))    )\\ _ )\\   _((_) ((_)      ((_)  (_))   ");print_wait();
    kprint("\n              | _ ) | |     (_)_\\(_) |_  /  | __|    / _ \\  / __| ");print_wait();
    kprint("\n              | _ \\ | |__    / _ \\    / /   | _|    | (_) | \\__ \\  ");print_wait();
    kprint("\n              |___/ |____|  /_/ \\_\\  /___|  |___|    \\___/  |___/  ");print_wait();
    kprint("\n  ");                                               
    kprint("\n              ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___");print_wait();

}

void print_about(){
    kprint("        Name: BlazeOS");print_wait();
    kprint("\n     Version: 0.0.0");print_wait();
    kprint("\n     Authors: Tyler Angelier, Rick Boles, Michael Montgomery");print_wait();
    kprint("\n    Compiler: i386elf-gcc");print_wait();
    kprint("\nTechnologies: qemu, nasm, gmp, mpfr, libmpc, gcc-4.9, binutils");print_wait();
    //TODO: get git link
    kprint("\n      GitHub: https://github.com/liketysplit/");print_wait();
    kprint("\n   Professor: Dr. Sudip Chakraborty");print_wait();
    kprint("\n      Course: CS4345 Operating Systems Fall 2018");print_wait();
    kprint("\nDate Started: Jan. 12th 2018");print_wait();
    //TODO: Update date
    kprint("\nDate Updated: April 23rd 2018");print_wait();
    kprint("\n   Languages: Assembly, C");print_wait();
    kprint("\n        Info: Paper on git.");print_wait();
}

void print_help(){
    //TODO: As you add commands, please add them here as well
    //TODO: Add a brief desc of each command
    kprint("Functions Available:\n  ABOUT\n  CLEAR\n  CREDITS\n  DEBUG\n  HELP\n  PAGE\n  SET COLOR <COLORNAME>\n  SHUTDOWN\n  SOURCES\n  TEST");
}

void print_credits(){
    kprint("\n");
    print_logo();
    wait();
    kprint("\n"); kprint("\n"); kprint("\n");    
    print_about();
    wait();
    kprint("\n"); kprint("\n"); kprint("\n");    
    print_sources();
    //TODO: Add Chakraborty's face to end of credits roll
    // wait();
    // kprint("\n");
    


}

void print_sources(){
    //TODO: Consult with Micke to get a fine tuned list of sources
    kprint(" OS Dev Wiki: https://forum.osdev.org/index.php");print_wait();
    kprint("\nLow Level EU: http://lowlevel.eu/");print_wait();

}

//Fast Wait Method
void print_wait(){
    int i = 0, j = 0;
    for(i;i<1250000;i++){
        for(j;j<100000000;j++){

        }
    } 
}
