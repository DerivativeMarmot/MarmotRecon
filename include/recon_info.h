#ifndef RECON_INHO_H
#define RECON_INHO_H

#include <stdio.h>
#include <stdlib.h> // rand()
#include <string.h> // memset
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h> // mkdir()
#include <unistd.h> // access()

#include "cJSON.h"

#define USER_JSON "User.json"
#define ITEM_JSON "resources/Item.json"
#define RECIPE_JSON "resources/RecipeBook.json"
#define MAX_SAVE 3
#define SAVE_ENTRY "resources/savedata/"
#define COMMON_PATH "resources/savedata/save%d/"
#define COLOR_GREEN "\033[;32m"
#define COLOR_RED "\033[;31m"
#define COLOR_YELLOW "\033[;33m"
#define COLOR_CYAN "\033[;36m"
#define COLOR_RESET "\033[0m"

// typedef struct {

// } mrSavedata_t;

typedef struct {
    char **map_clear; // reveal all position
    char **map_bool; // reveal only if the chara has ivisted
    int *shape;
} mrMap_t;
/*****************************************/
typedef struct {
    int level;
    int exp;
    double max_health;
    double health;
    double atk;
    double crit;
    double crit_dmg;
    bool duck;
    bool heal;
} mrAttr_t;
/*****************************************/
/*typedef struct {
    char *name;
    double attack;
} mrWeapon_t;

typedef struct {
    ;
} mrAccessory_t;
*/
typedef struct {
    struct {
        char *name;
        double attack;
    } *myWeapon;
    struct {
        ;
    } *myAccessory;
} mrEquipment_t;
/*****************************************/
typedef struct {
    char name[21];
    int position[2];
    mrAttr_t *myAttr;
    mrEquipment_t *myEquipment;
} mrEntity_t;
/*****************************************/
typedef struct {
    mrMap_t *myMap;
    mrEntity_t *myChara;
    mrEntity_t *myEnemy;
} mr_t;

#endif