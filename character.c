#include "character.h"
//#include "util.h"

char move(mrMap *myMap, int *pos, char direction){
    switch (direction)
    {
    case 'w': {
        if (pos[0] == 0)
            return 'x';
        else
            --pos[0];
        break;
    }
    case 's': {
        if (pos[0] == myMap->shape[0] - 1) // height
            return 'x';
        else
            ++pos[0];
        break;
    }
    case 'a': {
        if (pos[1] == 0)
            return 'x';
        else
            --pos[1];
        break;
    }
    case 'd': {
        // [pos[0] + 1] means the length of current row, for example 6
        // [pos[0] + 1] - 1 means the max index is 6-1=5
        if (pos[1] == myMap->shape[pos[0] + 1] - 1)
            return 'x';
        else
            ++pos[1];
        break;
    }
    default:
        break;
    }
    myMap->map_bool[pos[0]][pos[1]] = '1';
    return myMap->map_clear[pos[0]][pos[1]];
}

void chara_load(cJSON *json_chara, mrEntity *myChara){
    cJSON *json_position = cJSON_GetObjectItem(json_chara, "position");
    myChara->position[0] = cJSON_GetNumberValue(cJSON_GetArrayItem(json_position, 0));
    myChara->position[1] = cJSON_GetNumberValue(cJSON_GetArrayItem(json_position, 1));

    memcpy(myChara->name, cJSON_GetStringValue(cJSON_GetObjectItem(json_chara, "name")), 21);

    mrAttr *myAttr = myChara->myAttr;
    cJSON *json_attr = cJSON_GetObjectItem(json_chara, "Attribute");
    myAttr->max_health = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "max_health"));
    myAttr->health = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "health"));
    myAttr->atk = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "atk"));
    myAttr->crit = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "crit"));
    myAttr->crit_dmg = cJSON_GetNumberValue(cJSON_GetObjectItem(json_attr, "crit_dmg"));
    myAttr->duck = false;
    myAttr->heal = true;
}

void chara_write(cJSON *json_chara, mrEntity *myChara){
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

/*void interacts(mrMap *myMap, mrEntity *myChara, mrEntity *myEnemy){
    ;
}*/

void interacts_E(mrEntity *myChara, mrEntity *myEnemy, cJSON *json_inv){
    enemy_init(myEnemy);
    bool turn = true; // 1 chara turn, 0 enemy turn.
    double receiver_hp;
    char skill;
    mrEntity *active, *passive;
    int round = 1;
    while (1){
        if (turn){
            printf("%s-------------round %d-------------\n%s",COLOR_RED, round++, COLOR_RESET);
            skill_menu();
            skill = input_c("Your turn!");
            active = myChara;
            passive = myEnemy;
        }
        else{
            puts("Enemy turn!");
            skill = gen_randomInt(1, 6) + 48;
            active = myEnemy;
            passive = myChara;
        }
        
        switch (skill)
        {
        case '1':
            receiver_hp = skill_attack(active, passive);
            break;
        case '2':
            skill_duck(active);
            break;
        case '3':
            skill_powerUp(active);
            break;
        case '4':
            skill_powerDown(active);
            break;
        case '5':{
            if (active->myAttr->heal)
                skill_heal(active);
            else{
                colored_printS("You can't heal yourself anymore, running out of heal times\n", 31, 0);
                continue;
            }
            break;
        }
            
        default:
            continue;
        }

        if (receiver_hp <= 0){
            if (turn){
                colored_printS("You win!\n", 32, 0);
                battle_reward(json_inv);
            }else{
                colored_printS("You lose.\n", 31, 0);
            }
            break;
        }

        turn = !turn;
        colored_printS("TURN CHANGE\n", 33, 0);
        putchar(10);
    }
}

void interacts_M(cJSON *json_inv){
    int count = 3;
    char *sample[] = {"bronze", "iron", "gold"};
    int weight[] = {50, 40, 10};
    int index = weighted_randA(weight, count);
    inv_addItem(json_inv, sample[index], gen_randomInt(8, 15));
}

void interacts_G(cJSON *json_inv){
    int shape[2] = {3, 3};
    char *sample[][3] = {
        {"3_0", "3_1", "3_2"}, 
        {"4_0", "4_1", "4_2"}, 
        {"5_0", "5_1", "5_2"}
    };
    double weight[] = {75, 24, 1};
    char target[100];
    weighted_rand3DA(sample, weight, shape, target);
    printf("%sYou got %s!\n%s", COLOR_CYAN, target, COLOR_RESET);
}

/*cJSON *chara_load(mrEntity *myChara){
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