#ifndef CHARACTER_H
#define CHARACTER_H
#include "inventory.h"
#include "map.h"

char move(mrMap *, int *, char );
void position_load(cJSON *, int *);
void position_write(cJSON *, int *);
void interacts(cJSON *, mrMap *, mrChara *);

#endif