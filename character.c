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

void interacts(mrMap *myMap, mrChara *myChara, mrEnemy *myEnemy){
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
                colored_printS("You can not move in this direction anymore!", 2);
                break;
            default:
                break;
        }
        
        map_print(myMap, myChara->position);
        colored_printS("--------------------------\n", rand() % 6);
    }
}

void interacts_E(mrChara *myChara, mrEnemy *myEnemy){
    skill_menu();
    bool turn = true; // 1 chara turn, 0 enemy turn.
    double receiver_hp;
    for (int i=0; i<5; ++i){
        char skill;
        if (turn){
            skill = input_c("Your turn!");
        }
        else{
            puts("Enemy turn!");
            //skill = rand() % '2' +'1';
            skill = '1';
        }
        
        switch (skill)
        {
        case '1':
            receiver_hp = skill_attack(myChara->myAttr, myEnemy->myAttr, turn);
            break;
        
        default:
            continue;
        }

        if (receiver_hp <= 0){
            if (turn){
                colored_printS("You win!\n", 0);
            }else{
                colored_printS("You lose.\n", 2);
            }
            break;
        }

        turn = !turn;
    }
}
void interacts_M(){}

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