void print_logo(){
    
    blazePrint("\n              ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___");print_wait();
    blazePrint("\n ");
    blazePrint("\n                     (                   )              )    (   ");print_wait();
    blazePrint("\n                (    )\\ )     (       ( /(           ( /(    )\\ )  ");print_wait();
    blazePrint("\n              ( )\\  (()/(     )\\      )\\())  (       )\\())  (()/(  ");print_wait();
    blazePrint("\n              )((_)  /(_)) ((((_)(   ((_)\\   )\\     ((_)\\    /(_)) ");print_wait();
    blazePrint("\n             ((_)_  (_))    )\\ _ )\\   _((_) ((_)      ((_)  (_))   ");print_wait();
    blazePrint("\n              | _ ) | |     (_)_\\(_) |_  /  | __|    / _ \\  / __| ");print_wait();
    blazePrint("\n              | _ \\ | |__    / _ \\    / /   | _|    | (_) | \\__ \\  ");print_wait();
    blazePrint("\n              |___/ |____|  /_/ \\_\\  /___|  |___|    \\___/  |___/  ");print_wait();
    blazePrint("\n  ");                                               
    blazePrint("\n              ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___");print_wait();

}

void print_about(){
    blazePrint("        Name: BlazeOS");print_wait();
    blazePrint("\n     Version: 1.0.0");print_wait();
    blazePrint("\n     Authors: Tyler Angelier, Rick Boles, Michael Montgomery");print_wait();
    blazePrint("\n    Compiler: i386elf-gcc");print_wait();
    blazePrint("\nTechnologies: qemu, nasm, gmp, mpfr, libmpc, gcc-4.9, binutils");print_wait();
    //TODO: get git link
    blazePrint("\n      GitHub: https://github.com/liketysplit/");print_wait();
    blazePrint("\n   Professor: Dr. Sudip Chakraborty");print_wait();
    blazePrint("\n      Course: CS4345 Operating Systems Fall 2018");print_wait();
    blazePrint("\nDate Started: Jan. 12th 2018");print_wait();
    //TODO: Update date
    blazePrint("\nDate Updated: April 23rd 2018");print_wait();
    blazePrint("\n   Languages: Assembly, C");print_wait();
    blazePrint("\n        Info: Paper on git.");print_wait();
}

void print_help(){
    //TODO: As you add commands, please add them here as well
    //TODO: Add a brief desc of each command
    blazePrint("Functions Available:\n  ABOUT\n  CLEAR\n  CREDITS\n  DEBUG\n  HELP\n  PAGE\n  SET COLOR <COLORNAME>\n  SHUTDOWN\n  SOURCES\n  TEST");
}

void print_credits(){
    blazePrint("\n");
    print_logo();
    wait();
    blazePrint("\n"); blazePrint("\n"); blazePrint("\n");    
    print_about();
    wait();
    blazePrint("\n"); blazePrint("\n"); blazePrint("\n");    
    print_sources();
    //TODO: Add Chakraborty's face to end of credits roll
    // wait();
    // blazePrint("\n");
    


}

void print_sources(){
    //TODO: Consult with Micke to get a fine tuned list of sources
    blazePrint(" OS Dev Wiki: https://forum.osdev.org/index.php");print_wait();
    blazePrint("\nThe Little OS Book: http://littleosbook.github.io/");print_wait();
    blazePrint("\nLow Level EU: http://lowlevel.eu/");print_wait();
    blazePrint("\nGNU: http://www.gnu.org/");print_wait();
    

}

//Fast Wait Method
void print_wait(){
    int i = 0, j = 0;
    for(i;i<1250000;i++){
        for(j;j<100000000;j++){

        }
    } 
}
