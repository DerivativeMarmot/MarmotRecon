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


typedef struct Map{
    char **map_clear; // reveal all position
    char **map_bool; // reveal only if the chara has ivisted
    int *shape;
} mrMap;

typedef struct chara{
    int position[2];
    /*struct attr{
        double atk;
        double cri; // critical strike
    };*/
} mrChara;

typedef struct marmot_recon{
    mrMap *myMap;
    mrChara *myChara;
} marmotRecon;



#endif