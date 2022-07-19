#ifndef CHARACTER_H
#define CHARACTER_H
#include "inventory.h"
#include "map.h"
#include "skills.h"

char move(mrMap *, int *, char );
void chara_load(cJSON *, mrChara *);
void chara_write(cJSON *, mrChara *);
//void interacts(mrMap *, mrChara *, mrEnemy *);
void interacts_E(mrChara *, mrEnemy *);

#endif