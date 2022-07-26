#ifndef UTIL_H
#define UTIL_H
#include "recon_info.h"

cJSON *file2Json(char *);
char input_c(char *);
char *input_s(char *, int, char *);

// 0: reset
// color
// 31:red, 32 green, 33: yellow
// 34: blue, 35: Magenta, 36: Cyan
// 41: bg_red, 42: bg_green, 43: bg_yellow
// 44: bg_blue, 45: bg_magenta, 46: bg_cyan
// option
// 1: bold, 4: underline, 7: inverse
void colored_printC(char , int, int );

// 0: reset
// color
// 31:red, 32 green, 33: yellow
// 34: blue, 35: Magenta, 36: Cyan
// 41: bg_red, 42: bg_green, 43: bg_yellow
// 44: bg_blue, 45: bg_magenta, 46: bg_cyan
// option
// 1: bold, 4: underline, 7: inverse
void colored_printS(char *, int , int );

int gen_randomInt(int , int );
double gen_randomDouble(double , double );
char weighted_randC(char *, int *, int );
int weighted_randA(int *, int );

#endif