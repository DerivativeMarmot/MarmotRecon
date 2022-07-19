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

void chara_load(cJSON *json_chara, mrChara *myChara){
    cJSON *json_position = cJSON_GetObjectItem(json_chara, "position");
    myChara->position[0] = cJSON_GetNumberValue(cJSON_GetArrayItem(json_position, 0));
    myChara->position[1] = cJSON_GetNumberValue(cJSON_GetArrayItem(json_position, 1));

    memcpy(myChara->name, cJSON_GetStringValue(cJSON_GetObjectItem(json_chara, "name")), 21);

    mrAttr *myAttr = myChara->myAttr;
    cJSON *json_attr = cJSON_GetObjectItem(json_chara, "Attribute");
    myAttr->health = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "health"));
    myAttr->atk = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "atk"));
    myAttr->crit = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "crit"));
    myAttr->crit_dmg = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "crit_dmg"));
}

void chara_write(cJSON *json_chara, mrChara *myChara){
    // replace pos
    cJSON *json_position = cJSON_CreateIntArray(myChara->position, 2);
    cJSON_ReplaceItemInObjectCaseSensitive(json_chara, "position", json_position);

    // replace attr
    cJSON *json_attr = cJSON_CreateObject();
    mrAttr *myAttr = myChara->myAttr;
    cJSON_AddNumberToObject(json_attr, "health", myAttr->health);
    cJSON_AddNumberToObject(json_attr, "atk", myAttr->atk);
    cJSON_AddNumberToObject(json_attr, "crit", myAttr->crit);
    cJSON_AddNumberToObject(json_attr, "crit_dmg", myAttr->crit_dmg);
    cJSON_ReplaceItemInObjectCaseSensitive(json_chara, "Attribute", json_attr);
}

/*void interacts(mrMap *myMap, mrChara *myChara, mrEnemy *myEnemy){
    ;
}*/

void interacts_E(mrChara *myChara, mrEnemy *myEnemy){
    enemy_init(myEnemy);
    bool turn = true; // 1 chara turn, 0 enemy turn.
    double receiver_hp;
    char skill;
    while (1){
        if (turn){
            colored_printS("--------------------------\n", rand() % 6);
            skill_menu();
            skill = input_c("Your turn!");
        }
        else{
            puts("Enemy turn!");
            skill = gen_randomInt(1, 2) + 48;
        }
        
        switch (skill)
        {
        case '1':
            receiver_hp = skill_attack(myChara, myEnemy, turn);
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
        putchar(10);
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