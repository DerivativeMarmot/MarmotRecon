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

#define CHARACTER_JSON "Character.json"
#define ITEM_JSON "Item.json"
#define RECIPE_JSON "RecipeBook.json"

typedef struct Map{
    char **map_clear; // reveal all position
    bool **map_bool; // reveal only if the chara has ivisted
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