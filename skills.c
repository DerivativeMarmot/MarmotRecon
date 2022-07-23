#include "skills.h"

void skill_menu(){
    puts("\n\
    1. attck\n\
    2. duck\n\
    3. power up\n\
    4. power down\n\
    5. heal\
    ");
}

double skill_attack(mrEntity *active, mrEntity *passive){
    printf("%s%s is attacking %s%s\n", COLOR_RED, active->name, passive->name, COLOR_RESET);
    if (passive->myAttr->duck)
    {
        colored_printS("Miss!\n", 1);
        passive->myAttr->duck = !(passive->myAttr->duck);
        printf("%s%s duck point -1%s\n", COLOR_CYAN, passive->name, COLOR_RESET);
    }
    else
    {
        double atk = active->myAttr->atk;
        if (rand() % 100 <= active->myAttr->crit)
        {
            atk *= active->myAttr->crit_dmg;
            printf("%s%s deals a critical hit\n%s", COLOR_RED, active->name, COLOR_RESET);
        }
        passive->myAttr->health = passive->myAttr->health - atk < 0 ? 0 : passive->myAttr->health - atk;

        printf("%s deals %.2f to %s\n", active->name, atk, passive->name);
        printf("%s%s has %.2fhp remained\n%s", COLOR_CYAN, passive->name, passive->myAttr->health, COLOR_RESET);
    }
    return passive->myAttr->health;
}

void skill_duck(mrEntity *active){
    printf("%s%s duck point +1%s\n", COLOR_CYAN, active->name, COLOR_RESET);
    active->myAttr->duck = true;
}

void skill_powerUp(mrEntity *active){
    mrAttr *myAttr = active->myAttr;
    myAttr->health -= 5;
    myAttr->crit += 5;
    myAttr->atk += 2;
    printf("%s%s powered up!%s\n", COLOR_RED, active->name, COLOR_RESET);
    printf("\n\
    health: %.2f\n\
    crit: %.2f\n\
    atk: %.2f\n\
    ", myAttr->health, myAttr->crit, myAttr->atk);
}

void skill_powerDown(mrEntity *active){
    mrAttr *myAttr = active->myAttr;
    myAttr->health += 5;
    myAttr->crit -= 5;
    myAttr->atk -= 2;
    printf("%s%s powered down.%s\n", COLOR_RED, active->name, COLOR_RESET);
    printf("\n\
    health: %.2f\n\
    crit: %.2f\n\
    atk: %.2f\n", myAttr->health, myAttr->crit, myAttr->atk);
}

void skill_heal(mrEntity *active){
    mrAttr *myAttr = active->myAttr;
    myAttr->health += (myAttr->max_health - myAttr->health) / 2.0;
    myAttr->heal = false;
    printf("%s%s healed himself%s\n", COLOR_GREEN, active->name, COLOR_RESET);
    printf("health: %.2f",  myAttr->health);
}