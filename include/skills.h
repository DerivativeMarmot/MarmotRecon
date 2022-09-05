#ifndef SKILLS_H
#define SKILLS_H
#include "util.h"

void skill_menu();

// dir == 1 c attacks e, otherwise e attcks c
// returns the health value of who is attacked;
double skill_attack(mrEntity_t *, mrEntity_t *);

// Avoid receiving next damage from enemy
void skill_duck(mrEntity_t *);

void skill_powerUp(mrEntity_t *);
void skill_powerDown(mrEntity_t *);
void skill_armor();

// can only be used once in one battle
void skill_heal(mrEntity_t *);

#endif