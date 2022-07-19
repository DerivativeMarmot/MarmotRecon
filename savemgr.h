#ifndef SAVEMGR_H
#define SAVEMGR_H
#include "util.h"

cJSON *saveSelector(bool );
cJSON *userInit(char *);
cJSON *userLoad(char *);
void save2file(cJSON *);

#endif