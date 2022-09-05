#ifndef UTIL_H
#define UTIL_H
#include "recon_info.h"

cJSON *file2Json(char *filename);

// get user input (single character version)
char input_c(char *prompt);

// get user input (string version)
char *input_s(char *s, int length, char *prompt);

/* 
* print with color
* 0: reset
* color
* 31:red, 32 green, 33: yellow
* 34: blue, 35: Magenta, 36: Cyan
* 41: bg_red, 42: bg_green, 43: bg_yellow
* 44: bg_blue, 45: bg_magenta, 46: bg_cyan
* option
* 1: bold, 4: underline, 7: inverse
*/
void colored_printC(char c, int color, int option);

/* 
* print with color
* 0: reset
* color
* 31:red, 32 green, 33: yellow
* 34: blue, 35: Magenta, 36: Cyan
* 41: bg_red, 42: bg_green, 43: bg_yellow
* 44: bg_blue, 45: bg_magenta, 46: bg_cyan
* option
* 1: bold, 4: underline, 7: inverse
*/
void colored_printS(char *s, int color, int option);

int gen_randomInt(int min, int max);
double gen_randomDouble(double min, double max);

/*
sample: char array
weight: how each char is weighted
count: the length of sample
*/
char weighted_randC(char *sample, int *weight, int count);
int weighted_randA(int *weight, int count);
void weighted_rand3DA(char *(*sample)[3], double *weight, int *shape, char *target);

#endif