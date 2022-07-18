#ifndef CHARACTER_H
#define CHARACTER_H
#include "inventory.h"
#include "map.h"
#include "skills.h"

char move(mrMap *, int *, char );
void position_load(cJSON *, int *);
void position_write(cJSON *, int *);
void interacts(mrMap *, mrChara *, mrEnemy *);
void interacts_E(mrChara *, mrEnemy *);

#endif