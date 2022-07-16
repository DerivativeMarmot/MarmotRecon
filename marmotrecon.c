#include "map.h"
#include "character.h"
#include "inventory.h"
#include "savemgr.h"

int main(void){
    srand((unsigned)time(NULL));

    cJSON *json_main;
    //cJSON *json_item = file2Json(ITEM_JSON);
    //cJSON *json_recipe = file2Json(RECIPE_JSON);
    marmotRecon *myMR = (marmotRecon*) malloc (sizeof(marmotRecon));
    //marmotRecon *myMR;
    //myMR = malloc (sizeof( *myMR));
    mrMap *myMap = myMR->myMap;
    mrChara *myChara = myMR->myChara;
    myMap = (mrMap*) malloc (sizeof(mrMap));
    myChara = (mrChara*) malloc (sizeof(mrChara));
    //myMR->myMap = malloc (sizeof(*myMap));
    //myMR->myChara = malloc (sizeof(*myChara));
    // myMap = malloc (sizeof(*myMap));
    // myChara = malloc (sizeof(*myChara));

    char c;
    while (1){
        puts("\n\
    1. New game\n\
    2. Load\n\
    3. Quit\n\
    ");
        c = input_c("\0");
        if (c == '1'){
            json_main = saveSelector(true); // new game
            if (json_main == NULL)
                continue;
            map_init2(myMap);
            cJSON_AddItemToObject(json_main, "Map", map_write(myMap));
            break;
        }
        else if (c == '2'){
            json_main = saveSelector(false); // load game
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
    
    int pos[2];
    get_position(cJSON_GetObjectItem(json_main, "position"), pos);
    map_print2(myMap, pos);

    //cJSON *json_map = map_write(myMap);
    //cJSON_AddItemToObject(json_main, "Map", json_map);
    //printf(cJSON_Print(json_main));
    save2file(json_main);
    //cJSON_ReplaceItemInObjectCaseSensitive(json_main, "Map", NULL);
    
    /*int pos[2];
    get_position(cJSON_GetObjectItem(json_chara, "position"), pos);
    map_print(json_map, )
    cJSON_AddItemToObject(json_chara, "Map", json_map);

    //printf(cJSON_Print(json_chara));
    save2file(json_chara);*/
    

    
    
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



    
    
    
    // get_position(json_chara_pos, myChara->position);//
    //myChara->position[0] = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json_chara, "position"), 0)->valueint;
    //myChara->position[1] = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json_chara, "position"), 1)->valueint;
    
    
    // map_print2(myMap, myChara->position);//
    

    /*for (int i=0; i<10; i++){
        mrMapMenu();
        char c = input_c("> ");
        printf("%c\n", c);
        if (move(myMap, myChara->position, c) == 'x'){
            puts("You can not move in this direction anymore!");
        }
        mrMapPrint(myMap, myChara->position);
    }
    putchar(10);
    mrMapPrint(myMap, myChara->position);*/

    //save2file(json_chara);

    return 0;
}