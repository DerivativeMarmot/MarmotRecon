#include "skills.h"

void skill_menu(){
    puts("\n\
    1. attck\n\
    2. duck\n\
    ");
}

double skill_attack(mrAttr* cAttr, mrAttr* eAttr, bool turn){
    mrAttr *attacker, *receiver;
    if (turn){
        attacker = cAttr;
        receiver = eAttr;
    }else{
        attacker = eAttr;
        receiver = cAttr;
    }
    double atk = attacker->atk;
    receiver->health -= atk;
    printf("%s deals %.2f to %s\n", attacker->name, atk, receiver->name);
    printf("%s has %.2fhp remained\n", receiver->name, receiver->health);
    //colored_printS()
    return receiver->health;

}
/*void skill_duck(){}
void skill_powerUp(){}
void skill_powerDown(){}
void skill_heal(){}*/