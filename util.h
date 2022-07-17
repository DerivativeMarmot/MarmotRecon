#ifndef UTIL_H
#define UTIL_H
#include "recon_info.h"

cJSON *file2Json(char *);
char input_c(char *);
char *input_s(char *, int, char *);
void colored_printC(char , int);
void colored_printS(char *, int);

#endif