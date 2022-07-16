#ifndef MAP_H
#define MAP_H
#include "recon_info.h"

int gen_ran_bet(int , int );
//cJSON *map_init();
void map_init2(mrMap *);
void map_print(cJSON *, int *);
void map_print2(mrMap *, int *);
cJSON *map_write(mrMap *);
void map_load(mrMap *, cJSON *);
void mrMapMenu();

#endif