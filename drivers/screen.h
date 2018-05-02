#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
//#define WHITE_ON_BLACK 0x0f
//#define RED_ON_WHITE 0xf4

#define Light_Green_ON_BLACK 0x0a
#define Teal_ON_BLACK 0x0b
#define Orange_ON_WHITE 0xfc
#define Pink_ON_WHITE 0xfd
#define Yellow_ON_BLACK 0x0e
#define WHITE_ON_BLACK 0x0f

#define Dark_Blue_ON_WHITE 0xf1
#define Dark_Green_ON_WHITE 0xf2
#define Cyan_ON_WHITE 0xf3
#define RED_ON_WHITE 0xf4
#define Purple_ON_BLACK 0x05
#define Brown_ON_WHITE 0xf6
#define Light_Grey_ON_BLACK 0x07
#define Dark_Grey_ON_WHITE 0xf8
#define Light_BLue_ON_BLACK 0x09
#define Black_ON_WHITE 0xf0

#define G 0x04

/*
A= Light Green
B= Teal
C= Orange
D= Pink
E= Yellow
F= White

1= Dark Blue
2= Dark Green
3= Cyan
4= Red
5= Purple
6= Brown
7= Light Grey
8= Dark Grey
9= Light BLue
0= Black

*/

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5


void clear_screen();
void blazePrint_at(char *message, int col, int row);
void blazePrint(char *message);
void blazePrint_backspace();
void setcolor(char);

#endif
