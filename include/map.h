#ifndef MAP_H
#define MAP_H
#include "util.h"

void map_init(mrMap *);
void map_print(mrMap *, int *);
cJSON *map_write(mrMap *);
void map_load(mrMap *, cJSON *);
void map_free(int *, char **, char **);
void map_menu();

#endif