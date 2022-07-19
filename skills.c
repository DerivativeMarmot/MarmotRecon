#include "skills.h"

void skill_menu(){
    puts("\n\
    1. attck\n\
    2. duck\n\
    ");
}

void enemy_init(mrEnemy *myEnemy){
    mrAttr *myAttr = myEnemy->myAttr;
    memcpy(myEnemy->name, "Bad marmot", strlen("Bad marmot")+1);
    myAttr->health = gen_randomInt(20, 25);
    myAttr->atk = gen_randomInt(1, 5);
    myAttr->crit = gen_randomDouble(3, 5);
    myAttr->crit_dmg = 1.5;
}

double skill_attack(mrChara *myChara, mrEnemy *myEnemy, bool turn){
    char *attacker_name, *receiver_name;
    mrAttr *attacker, *receiver;
    if (turn){
        attacker = myChara->myAttr;
        receiver = myEnemy->myAttr;
        attacker_name = myChara->name;
        receiver_name = myEnemy->name;
    }else{
        attacker = myEnemy->myAttr;
        receiver = myChara->myAttr;
        attacker_name = myEnemy->name;
        receiver_name = myChara->name;
    }
    double atk = attacker->atk;
    if (rand() % 100 <= attacker->crit){
        atk *= attacker->crit_dmg;
        printf("%s%s deals a critical hit\n%s",COLOR_RED, attacker_name, COLOR_RESET);
    }
    receiver->health = receiver->health - atk < 0 ? 0 : receiver->health - atk;
    
    printf("%s deals %.2f to %s\n", attacker_name, atk, receiver_name);
    printf("%s%s has %.2fhp remained\n%s", COLOR_CYAN, receiver_name, receiver->health, COLOR_RESET);
    //colored_printS()
    return receiver->health;

}
/*void skill_duck(){}
void skill_powerUp(){}
void skill_powerDown(){}
void skill_heal(){}*/