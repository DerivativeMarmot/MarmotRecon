#include "map.h"
#include "character.h"
#include "inventory.h"
#include "savemgr.h"

int main(void){
    srand((unsigned)time(NULL));

    cJSON *json_chara;
    //cJSON *json_item = file2Json(ITEM_JSON);
    //cJSON *json_recipe = file2Json(RECIPE_JSON);

    char c;
    while (1){
        puts("\n\
    1. New game\n\
    2. Load\n\
    3. Quit\n\
    ");
        c = input_c("\0");
        if (c == '1'){
            json_chara = saveSelector(true); // new game
            if (json_chara == NULL)
                continue;
            break;
        }
        else if (c == '2'){
            json_chara = saveSelector(false); // load game
            if (json_chara == NULL)
                continue;
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
    

    
    
    //cJSON *json_user = file2Json(CHARACTER_JSON);
    //cJSON *json_item = file2Json(ITEM_JSON);
    //cJSON *json_recipe = file2Json(RECIPE_JSON);
    //inv_print(cJSON_GetObjectItemCaseSensitive(json_CharaAttr, "Inventory"));
    //cJSON *json_chara_pos = cJSON_GetObjectItemCaseSensitive(json_chara, "position");
    cJSON *json_inv = cJSON_GetObjectItemCaseSensitive(json_chara, "Inventory");
    inv_print(json_inv);
    putchar(10);
    inv_addItem(json_inv, "iron", 22);
    inv_addItem(json_inv, "bronze", 12);
    inv_print(json_inv);



    
    marmotRecon *myMR;
    mrMap *myMap = myMR->myMap;
    mrChara *myChara = myMR->myChara;
    myMap = (mrMap*) malloc (sizeof(mrMap));
    myChara = (mrChara*) malloc (sizeof(mrChara));
    
    myChara->position[0] = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json_chara, "position"), 0)->valueint;
    myChara->position[1] = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json_chara, "position"), 1)->valueint;
    
    mrMapInit(myMap);
    mrMapPrint(myMap, myChara->position);
    

    for (int i=0; i<10; i++){
        mrMapMenu();
        char c = input_c("> ");
        printf("%c\n", c);
        if (move(myMap, myChara->position, c) == 'x'){
            puts("You can not move in this direction anymore!");
        }
        mrMapPrint(myMap, myChara->position);
    }
    putchar(10);
    mrMaPrint(myMap, myChara->position);

    save2file(json_chara, myMap);

    return 0;
}