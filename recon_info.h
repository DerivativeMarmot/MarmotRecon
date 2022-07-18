#ifndef RECON_INHO_H
#define RECON_INHO_H

#include <stdio.h>
#include <stdlib.h> // rand()
#include <string.h> // memset
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h> // mkdir()
#include <unistd.h> // access()

#include "cJSON/cJSON.h"
#include "util.h"

#define USER_JSON "User.json"
#define ITEM_JSON "Item.json"
#define RECIPE_JSON "RecipeBook.json"
#define MAX_SAVE 3
#define COMMON_PATH "savedata/save%d/"


typedef struct{
    char **map_clear; // reveal all position
    char **map_bool; // reveal only if the chara has ivisted
    int *shape;
} mrMap;

typedef struct{
    char name[30];
    double health;
    double atk;
    double crit;
    double crit_dmg;
} mrAttr;

typedef struct{
    int position[2];
    mrAttr *myAttr;
} mrChara;

typedef struct{
    mrAttr *myAttr;
} mrEnemy;

typedef struct{
    mrMap *myMap;
    mrChara *myChara;
    mrEnemy *myEnemy;
} marmotRecon;

#endif