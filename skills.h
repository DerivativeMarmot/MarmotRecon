#ifndef SKILLS_H
#define SKILLS_H
#include "recon_info.h"

void skill_menu();

// dir == 1 c attacks e, otherwise e attcks c
// returns the health value of who is attacked;
double skill_attack(mrAttr *, mrAttr *, bool );

// Do not receive next damage from enemy
void skill_duck();
void skill_powerUp();
void skill_powerDown();
void skill_armor();
void skill_heal();

#endif