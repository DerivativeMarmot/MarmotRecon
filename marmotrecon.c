#include "character.h"
#include "savemgr.h"

int main(void){
    srand((unsigned)time(NULL));

    cJSON *json_main;
    
    marmotRecon *myMR = (marmotRecon*) malloc (sizeof(marmotRecon));

    mrMap *myMap = myMR->myMap;
    mrChara *myChara = myMR->myChara;
    mrEnemy *myEnemy = myMR->myEnemy;

    myMap = (mrMap*) malloc (sizeof(mrMap));

    myChara = (mrChara*) malloc (sizeof(mrChara));
    myChara->myAttr = (mrAttr*) malloc (sizeof(mrAttr));

    myEnemy = (mrEnemy*) malloc (sizeof(mrEnemy));
    myEnemy->myAttr = (mrAttr*) malloc (sizeof(mrAttr));

    char c;
    while (1){
        puts("\n\
    1. New game\n\
    2. Load\n\
    3. Quit\n\
    ");
        c = input_c("\0");
        if (c == '1'){ // new game
            json_main = saveSelector(true); // create json_main
            if (json_main == NULL)
                continue;
            map_init(myMap); // generate map
            cJSON_AddItemToObject(json_main, "Map", map_write(myMap)); // add map to json_main
            break;
        }
        else if (c == '2'){ // load game
            json_main = saveSelector(false);
            if (json_main == NULL)
                continue;
            //printf(cJSON_Print(json_main));
            map_load(myMap, cJSON_GetObjectItem(json_main, "Map"));
            break;
        }
        else if (c == '3'){
            puts("Terminating the program...");
            return 0;
        }
        else {
            c = input_c("\0");
        }
    }

    position_load(cJSON_GetObjectItem(json_main, "position"), myChara->position);
    map_print(myMap, myChara->position);

    interacts(myMap, myChara, myEnemy);
    
    cJSON_ReplaceItemInObjectCaseSensitive(json_main, "Map", map_write(myMap));
    position_write(cJSON_GetObjectItem(json_main, "position"), myChara->position);
    save2file(json_main);

    //cJSON *json_user = file2Json(CHARACTER_JSON);
    //cJSON *json_item = file2Json(ITEM_JSON);
    //cJSON *json_recipe = file2Json(RECIPE_JSON);
    //inv_print(cJSON_GetObjectItemCaseSensitive(json_CharaAttr, "Inventory"));
    // cJSON *json_chara_pos = cJSON_GetObjectItemCaseSensitive(json_main, "position");//
    /*cJSON *json_inv = cJSON_GetObjectItemCaseSensitive(json_chara, "Inventory");
    inv_print(json_inv);
    putchar(10);
    inv_addItem(json_inv, "iron", 22);
    inv_addItem(json_inv, "bronze", 12);
    inv_print(json_inv);*/

    return 0;
}