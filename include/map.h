#ifndef MAP_H
#define MAP_H
#include "util.h"

void map_init(mrMap_t *);
void map_print(mrMap_t *, int *);
cJSON *map_write(mrMap_t *);
void map_load(mrMap_t *, cJSON *);
void map_free(int *, char **, char **);
void map_menu();

#endif