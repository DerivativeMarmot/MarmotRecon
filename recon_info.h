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

#define USER_JSON "User.json"
#define ITEM_JSON "Item.json"
#define RECIPE_JSON "RecipeBook.json"
#define MAX_SAVE 3
#define COMMON_PATH "savedata/save%d/"
#define COLOR_GREEN "\033[;32m"
#define COLOR_RED "\033[;31m"
#define COLOR_YELLOW "\033[;33m"
#define COLOR_CYAN "\033[;36m"
#define COLOR_RESET "\033[0m"


typedef struct{
    char **map_clear; // reveal all position
    char **map_bool; // reveal only if the chara has ivisted
    int *shape;
} mrMap;

typedef struct{
    int level;
    int exp;
    double health;
    double atk;
    double crit;
    double crit_dmg;
} mrAttr;

typedef struct{
    char name[21];
    int position[2];
    mrAttr *myAttr;
} mrChara;

typedef struct{
    char name[21];
    mrAttr *myAttr;
} mrEnemy;

typedef struct{
    mrMap *myMap;
    mrChara *myChara;
    mrEnemy *myEnemy;
} marmotRecon;

#endif