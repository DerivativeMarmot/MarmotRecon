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

    char *main_menu = "\n\
    1. New game\n\
    2. Load\n\
    3. Quit\n";
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
            puts("Terminating the program...");
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
        char dir = input_c("\0");
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
    cJSON_ReplaceItemInObjectCaseSensitive(json_main, "Map", map_write(myMap));
    chara_write(json_main, myChara);
    save2file(json_main);

    return 0;
}