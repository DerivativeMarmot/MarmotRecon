#ifndef SKILLS_H
#define SKILLS_H
#include "util.h"

void skill_menu();

// dir == 1 c attacks e, otherwise e attcks c
// returns the health value of who is attacked;
double skill_attack(mrEntity *, mrEntity *);

// Avoid receiving next damage from enemy
void skill_duck(mrEntity *);

void skill_powerUp(mrEntity *);
void skill_powerDown(mrEntity *);
void skill_armor();

// can only be used once in one battle
void skill_heal(mrEntity *);

#endif