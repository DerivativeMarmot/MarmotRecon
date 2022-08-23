#ifndef INVENTORY_H
#define INVENTORY_H
#include "util.h"

void inv_print(cJSON *);
void inv_addItem(cJSON *, char* , int );
void inv_subItem(cJSON *, char* , int );
void inv_deleteItem(cJSON *, char*);
void inv_menu();

#endif