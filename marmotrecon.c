#include "character.h"
#include "savemgr.h"

int main(void){
    srand((unsigned)time(NULL));

    cJSON *json_main;
    
    marmotRecon *myMR = (marmotRecon*) malloc (sizeof(marmotRecon));

    mrMap *myMap = myMR->myMap;
    mrEntity *myChara = myMR->myChara;
    mrEntity *myEnemy = myMR->myEnemy;

    myMap = (mrMap*) malloc (sizeof(mrMap));

    myChara = (mrEntity*) malloc (sizeof(mrEntity));
    myChara->myAttr = (mrAttr*) malloc (sizeof(mrAttr));

    myEnemy = (mrEntity*) malloc (sizeof(mrEntity));
    myEnemy->myAttr = (mrAttr*) malloc (sizeof(mrAttr));
/***********************************************/

    char c;
    while (1){
        puts("\n\
    1. New game\n\
    2. Load\n\
    3. Quit\n\
    ");
        c = input_c("\0");
        if (c == '1'){ // new game
            json_main = saveSelector(true);
            if (json_main == NULL)
                continue;
            map_init(myMap); // generate map
            cJSON_AddItemToObject(json_main, "Map", map_write(myMap)); // add map to json_main
            save2file(json_main);
            break;
        }
        else if (c == '2'){ // load game
            json_main = saveSelector(false);
            if (json_main == NULL)
                continue;
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
    putchar(10);
/***********************************************/
    
    cJSON *json_inv = cJSON_GetObjectItem(json_main, "Inventory");
    
    printf("Welcome back %s\n", myChara->name);
    chara_load(json_main, myChara); // name, pos, attr
    map_print(myMap, myChara->position);
    while (1){
        map_menu();
        char dir = input_c("\0");
        if (dir == 'q')
            break;
        
        switch ( move( myMap, myChara->position, dir ) )
        {
            case 'E':
                colored_printS("Enemy found, get into fight!\n", 33, 0);
                interacts_E(myChara, myEnemy, json_inv);
                break;
            case 'M':
                puts("Mineral");
                break;
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
    cJSON_ReplaceItemInObjectCaseSensitive(json_main, "Map", map_write(myMap));
    chara_write(json_main, myChara);
    save2file(json_main);

    return 0;
}