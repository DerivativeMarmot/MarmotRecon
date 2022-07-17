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
        if (pos[0] == height - 1){
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
    myMap->map_bool[pos[0]][pos[1]] = '1';
    return myMap->map_clear[pos[0]][pos[1]];
}

void position_load(cJSON *json_position, int *pos){
    pos[0] = cJSON_GetNumberValue(cJSON_GetArrayItem(json_position, 0));
    pos[1] = cJSON_GetNumberValue(cJSON_GetArrayItem(json_position, 1));
}

void position_write(cJSON *json_position, int *pos){
    cJSON_SetNumberHelper(cJSON_GetArrayItem(json_position, 0), pos[0]);
    cJSON_SetNumberHelper(cJSON_GetArrayItem(json_position, 1), pos[1]);
}

void interacts(cJSON *json, mrMap *myMap, mrChara *myChara){
    position_load(cJSON_GetObjectItem(json, "position"), myChara->position);
    map_print(myMap, myChara->position);

    for (int i=0; i<10; i++){
        mrMapMenu();
        char dir = input_c("\0");
        if (dir == 'q')
            break;
        
        switch ( move( myMap, myChara->position, dir ) )
        {
            case 'E':
                puts("Enemy");
                break;
            case 'M':
                puts("Mineral");
                break;
            case '*':
                puts("None");
                break;
            case 'x':
                colored_printS("You can not move in this direction anymore!", 2);
                break;
            default:
                break;
        }

        map_print(myMap, myChara->position);
        colored_printS("--------------------------", rand() % 6);
    }
    putchar(10);
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