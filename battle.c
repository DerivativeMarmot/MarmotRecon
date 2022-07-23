#include "battle.h"

void enemy_init(mrEntity *myEnemy){
    mrAttr *myAttr = myEnemy->myAttr;
    memcpy(myEnemy->name, "Bad marmot", strlen("Bad marmot")+1);
    myAttr->max_health = gen_randomInt(20, 25);
    myAttr->health = myAttr->max_health;
    myAttr->atk = gen_randomInt(1, 5);
    myAttr->crit = gen_randomDouble(3, 5);
    myAttr->crit_dmg = 1.5;
    myAttr->duck = false;
    myAttr->heal = true;
}

void battle_reward(cJSON *json_inv){
    inv_addItem(json_inv, "bronze", gen_randomInt(2, 5));
}