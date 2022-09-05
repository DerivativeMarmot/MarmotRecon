#ifndef SAVEMGR_H
#define SAVEMGR_H
#include "util.h"

// check if a save exists
void save_existence(bool *save_status, char *pattern_dir, int len_dir);

// option == true means new game, otherwise load a save
cJSON *saveSelector(bool );
cJSON *userInit(char *);
cJSON *userLoad(char *);
void save2file(cJSON *);
void delete_save();

#endif