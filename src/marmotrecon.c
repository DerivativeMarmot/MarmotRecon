#include "character.h"
#include "savemgr.h"

int main(void){
    srand((unsigned)time(NULL));

    cJSON *json_main;
    
    mr_t *myMR = (mr_t*) malloc (sizeof(mr_t));

    mrMap_t *myMap = myMR->myMap;
    mrEntity_t *myChara = myMR->myChara;
    mrEntity_t *myEnemy = myMR->myEnemy;

    myMap = (mrMap_t*) malloc (sizeof(mrMap_t));

    myChara = (mrEntity_t*) malloc (sizeof(mrEntity_t));
    myChara->myAttr = (mrAttr_t*) malloc (sizeof(mrAttr_t));

    myEnemy = (mrEntity_t*) malloc (sizeof(mrEntity_t));
    myEnemy->myAttr = (mrAttr_t*) malloc (sizeof(mrAttr_t));
/***********************************************/

    char *main_menu = "\n\
    1. New game\n\
    2. Load\n\
    3. Delete\n\
    q. Quit\n";
    bool ifContinue = true;
    while (ifContinue){
        switch (input_c(main_menu))
        {
        case '1': {
            json_main = saveSelector(true);
            if (json_main == NULL){
                colored_printS("Failed to create save file\n", 31, 0);
                continue;
            }
            map_init(myMap); // generate map
            cJSON_AddItemToObject(json_main, "Map", map_write(myMap)); // add map to json_main
            save2file(json_main);
            ifContinue = false;
            break;
        }
        case '2': {
            json_main = saveSelector(false);
            if (json_main == NULL)
                if (json_main == NULL){
                colored_printS("Failed to load save file\n", 31, 0);
                continue;
            }
            map_load(myMap, cJSON_GetObjectItem(json_main, "Map"));
            ifContinue = false;
            break;
        }
        case '3': {
            delete_save();
            break;
        }
        case 'q': {
            puts("Terminating the program...");
            puts("Good bye");
            return 0;
        }
        default:
            ;
        }
    }
    putchar(10);
/***********************************************/
    
    cJSON *json_inv = cJSON_GetObjectItem(json_main, "Inventory");
    
    printf("Welcome back %s\n", myChara->name);
    chara_load(json_main, myChara); // name, pos, attr
    map_print(myMap, myChara->position);
    while (1){
        map_menu();
        char dir = input_c("\0"); // direction
        if (dir == 'q')
            break;
        
        switch ( move( myMap, myChara->position, dir ) )
        {
            case 'E':
            {
                colored_printS("Enemy found!\n", 33, 0);
                switch (input_c("1. fight\n2. run away"))
                {
                case '1':
                    interacts_E(myChara, myEnemy, json_inv);
                    break;
                case '2':
                default:
                    break;
                }
                break;
            }
            case 'M':
                puts("Mineral");
                interacts_M(json_inv);
                break;
            case 'G':{
                puts("Gacha");
                interacts_G(json_inv);
                break;
            }
            case '*':
                puts("None");
                break;
            case 'x':
                colored_printS("You can not move in this direction anymore!\n", 31, 0);
                break;
            default:
                break;
        }
        
        map_print(myMap, myChara->position);
    }

    // save current staus to file
    cJSON_ReplaceItemInObjectCaseSensitive(json_main, "Map", map_write(myMap));
    chara_write(json_main, myChara);
    save2file(json_main);

    // free

    return 0;
}