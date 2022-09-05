#ifndef CHARACTER_H
#define CHARACTER_H
#include "map.h"
#include "battle.h"

char move(mrMap_t *, int *, char );
void chara_load(cJSON *, mrEntity_t *);
void chara_write(cJSON *, mrEntity_t *);
void interacts_E(mrEntity_t *, mrEntity_t *, cJSON *);
void interacts_M(cJSON *json_inv);
void interacts_G(cJSON *json_inv);
void show_property(mrEntity_t *myChara);

#endif