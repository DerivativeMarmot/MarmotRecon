#include "character.h"
//#include "util.h"

char move(mrMap *myMap, int *pos, char direction){
    int height = myMap->shape[0];
    if (direction == 'w'){
        if (pos[0] == 0){
            return 'x';
        }else{
            --pos[0];
        }
    }
    else if (direction == 's'){
        if (pos[0] == myMap->shape[0] - 1){
            return 'x';
        }else{
            ++pos[0];
        }
    }
    else if (direction == 'a'){
        if (pos[1] == 0)
            return 'x';
        else{
            --pos[1];
        }
    }
    else if (direction == 'd'){
        // [pos[0] + 1] means the length of current row, for example 6
        // [pos[0] + 1] - 1 means the max index is 6-1=5
        if (pos[1] == myMap->shape[pos[0] + 1] - 1){
            return 'x';
        }else{
            ++pos[1];
        }
    }
    myMap->map_bool[pos[0]][pos[1]] = true;
    return myMap->map_clear[pos[0]][pos[1]];
}



/*cJSON *chara_load(mrChara *myChara){
    cJSON *json_CharaAttr = file2Json(CHARACTER_JSON);
}
void chara_write(){;}*/

/*char goUp(mrMap *myMap){
    ;
}
char goDown(mrMap *myMap){
    ;
}
char goLeft(mrMap *myMap){
    ;
}
char goRight(mrMap *myMap){
    ;
}*/