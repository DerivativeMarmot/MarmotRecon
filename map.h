#ifndef MAP_H
#define MAP_H
#include "recon_info.h"

int gen_ran_bet(int , int );
void map_init(mrMap *);
void map_print(mrMap *, int *);
cJSON *map_write(mrMap *);
void map_load(mrMap *, cJSON *);
void map_free(int *, char **, char **);
void mrMapMenu();

#endif