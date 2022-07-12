#include "map.h"
#include "character.h"

int main(void){
    srand((unsigned)time(NULL));
    marmotRecon *myMR;
    myMR->myMap = (mrMap*) malloc (sizeof(mrMap));
    myMR->myChara = (mrChara*) malloc (sizeof(mrChara));

    myMR->myChara->position[0] = 0;
    myMR->myChara->position[1] = 0;
    
    
    mrMap_gen_raw(myMR->myMap);
    mrMap_print(myMR->myMap);
    for (int i=0; i<10; i++){
        if (move(myMR->myMap, myMR->myChara->position, 's') == 'x'){
            puts("You can not move in this direction anymore!");
        }
    }
    putchar(10);
    mrMap_print(myMR->myMap);
    return 0;
}