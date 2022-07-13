#include "map.h"
#include "character.h"
#include "inventory.h"
#include "util.h"

int main(void){
    srand((unsigned)time(NULL));
    
    cJSON *json_chara = file2Json(CHARACTER_JSON);
    //inv_print(cJSON_GetObjectItemCaseSensitive(json_CharaAttr, "Inventory"));
    cJSON *json_chara_pos = cJSON_GetObjectItemCaseSensitive(json_chara, "position");
    cJSON *json_inv = cJSON_GetObjectItemCaseSensitive(json_chara, "Inventory");
    inv_print(json_inv);
    putchar(10);
    inv_addItem(json_inv, "iron", 22);
    inv_addItem(json_inv, "bronze", 12);
    inv_print(json_inv);



    
    /*marmotRecon *myMR;
    myMR->myMap = (mrMap*) malloc (sizeof(mrMap));
    myMR->myChara = (mrChara*) malloc (sizeof(mrChara));

    myMR->myChara->position[0] = json_chara_pos->child->valuedouble;
    myMR->myChara->position[1] = json_chara_pos->child->next->valuedouble;
    
    mrMap_gen_raw(myMR->myMap);
    mrMap_print(myMR->myMap, myMR->myChara->position);
    

    for (int i=0; i<10; i++){
        mrMap_menu();
        char c = input("> ");
        printf("%c\n", c);
        if (move(myMR->myMap, myMR->myChara->position, c) == 'x'){
            puts("You can not move in this direction anymore!");
        }
        mrMap_print(myMR->myMap, myMR->myChara->position);
    }
    putchar(10);
    mrMap_print(myMR->myMap, myMR->myChara->position);*/

    

    return 0;
}