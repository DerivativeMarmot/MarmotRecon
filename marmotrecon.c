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
    
    printf("Welcome back %s\n", myChara->name);
    chara_load(json_main, myChara); // name, pos, attr
    map_print(myMap, myChara->position);
    for (int i=0; i<10; i++){
        map_menu();
        char dir = input_c("\0");
        if (dir == 'q')
            break;
        
        switch ( move( myMap, myChara->position, dir ) )
        {
            case 'E':
                puts("Enemy");
                interacts_E(myChara, myEnemy);
                break;
            case 'M':
                puts("Mineral");
                break;
            case '*':
                puts("None");
                break;
            case 'x':
                colored_printS("You can not move in this direction anymore!\n", 2);
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