#ifndef CHARACTER_H
#define CHARACTER_H
#include "map.h"
#include "battle.h"

char move(mrMap *, int *, char );
void chara_load(cJSON *, mrEntity *);
void chara_write(cJSON *, mrEntity *);
//void interacts(mrMap *, mrEntity *, mrEntity *);
void interacts_E(mrEntity *, mrEntity *, cJSON *);
void interacts_M(cJSON *json_inv);
void interacts_G(cJSON *json_inv);

#endif