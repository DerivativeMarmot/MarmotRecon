#include "savemgr.h"

void save_existence(bool *save_status, char *pattern_dir, int len_dir){
    char save_dir[len_dir];
    for (int i=0; i<MAX_SAVE; ++i){
        // allocate string of savepath
        sprintf(save_dir, pattern_dir, i);

        // 0 on success, -1 on fail
        // F_OK -> existence
        if (access(save_dir, F_OK) == 0){
            printf("%4c%s%d. save %d exists\n%s", ' ', COLOR_GREEN, i, i, COLOR_RESET);
            save_status[i] = true;
        }else{
            printf("%4c%s%d. save %d is empty\n%s", ' ', COLOR_RED, i, i, COLOR_RESET);
            save_status[i] = false;
        }
    }
    printf("%4c%s\n", ' ', "q. Go back");
}

cJSON *saveSelector(bool option){
    // pattern
    int len_dir = strlen(COMMON_PATH) + 1;
    int len_path = strlen(COMMON_PATH) + strlen(USER_JSON) + 1;
    char pattern_dir[len_dir];
    char pattern_path[len_path];
    memset(pattern_dir, '\0', len_dir);
    memset(pattern_path, '\0', len_path);
    strcpy(pattern_dir, COMMON_PATH);
    sprintf(pattern_path, "%s%s", COMMON_PATH, USER_JSON);

    // prompt usable saves
    bool save_status[MAX_SAVE];
    save_existence(save_status, pattern_dir, len_dir);

    // let user select a save
    int save_i = input_c("Select a save") - 48;
    if (save_i >= 0 && save_i < MAX_SAVE){ // save0 ~ save9

        // pattern -> real
        char save_dir[len_dir];
        char save_path[len_path];
        sprintf(save_dir, pattern_dir, save_i);
        sprintf(save_path, pattern_path, save_i);
        
        // new game
        if (option){
            if (access(SAVE_ENTRY, F_OK) == -1)
                mkdir(SAVE_ENTRY, S_IRWXU); // 700
            // overwrite exsiting game
            if (save_status[save_i]){
                colored_printS("This is a existing save. Are you sure to overwrite it?(y/n)", 33, 0);
                char yn = input_c("\0");
                while (1){
                    if (yn == 'Y' || yn == 'y'){
                        puts("Save overwrited");
                        break;
                    }
                    else if (yn == 'N' || yn == 'n'){
                        puts("Operation cancelled.");
                        return NULL;
                    }
                    else
                        yn = input_c("Invalid Input");
                }
            }
            mkdir(save_dir, S_IRWXU); // 700
            return userInit(save_path);
        }
        
        // load game
        else{
            return userLoad(save_path);
        }
    }else if (save_i == 'q'-48){
        ;
    }else{
        puts("No such file");
    }

    return NULL;
}

cJSON *userInit(char *savepath){
    cJSON *user_json = cJSON_CreateObject();

    // create username
    char username[21];
    do{
        memset(username, 0, sizeof(username));
        if (input_s(username, 21, "Username (Maximum of 20 characters)")){
            printf("Please confirm your username(y/n): %s\n", username);
            char c = input_c("\0");
            if (c == 'Y' || c == 'y'){
                puts("Username confirmed.");
                break;
            }else if (c == 'N' || c == 'n'){
                puts("Enter Username again.");
            }else{
                ;
            }
        }
    } while(1);
    cJSON_AddStringToObject(user_json, "name", username);

    // create savepath
    cJSON_AddStringToObject(user_json, "savepath", savepath);

    // create position
    int pos[2] = {0, 0};
    cJSON_AddItemToObject(user_json, "position", cJSON_CreateIntArray(pos, 2));

    // create inventory
    cJSON_AddItemToObject(user_json, "Inventory", cJSON_CreateObject());

    // create attribute
    cJSON *json_attr  = cJSON_CreateObject();
    double max_health = gen_randomInt(50, 60);
    cJSON_AddNumberToObject(json_attr, "max_health", max_health);
    cJSON_AddNumberToObject(json_attr, "health", max_health);
    cJSON_AddNumberToObject(json_attr, "atk", gen_randomInt(5, 8));
    cJSON_AddNumberToObject(json_attr, "crit", gen_randomDouble(5, 10));
    cJSON_AddNumberToObject(json_attr, "crit_dmg", 1.5);
    cJSON_AddItemToObject(user_json, "Attribute", json_attr);

    // create basic weapon
    cJSON *json_weapon = cJSON_CreateObject();
    const char *const weapon_name = "Edgeless Sword";
    cJSON *json_basic_weapon = cJSON_CreateObject();
    cJSON_AddStringToObject(json_basic_weapon, "name", weapon_name);
    cJSON_AddNumberToObject(json_basic_weapon, "attack_damage", gen_randomInt(1, 3));
    cJSON_AddItemToObject(json_weapon, weapon_name, json_basic_weapon);
    cJSON_AddItemToObject(user_json, "Weapon", json_weapon);

    return user_json;
}

cJSON *userLoad(char *savepath){
    return file2Json(savepath);
}

void save2file(cJSON *json){
    char *savepath = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(json, "savepath"));
    FILE *fp = fopen(savepath, "w");
    if (fp){
        char *json2str = cJSON_Print(json);
        fwrite(json2str, strlen(json2str), 1, fp);
        free(json2str);
        fclose(fp);
        colored_printS("Successfully save to file", 32, 0);
    }else{
        fprintf(stderr, "failed to open %s", savepath);
    }
}

void delete_save(){
    bool save_status[MAX_SAVE];
    save_existence(save_status, COMMON_PATH, strlen(COMMON_PATH)+1);
    char save_i = input_c("The save you want to delete(0-9)") - 48;
    if (save_i >= 0 && save_i < MAX_SAVE){
        if (save_status[save_i]){
            char cmd_prefix[] = "rm -rf ";
            int len_cmd = strlen(cmd_prefix) + strlen(COMMON_PATH);
            char cmd[len_cmd + 1];
            strcpy(cmd, cmd_prefix);
            strcat(cmd, COMMON_PATH);
            sprintf(cmd, cmd, save_i);
            cmd[len_cmd] = '\0';

            if (system(cmd) == 0)
                colored_printS("Save deleted successfully\n", 32, 0);
            else
                colored_printS("Unable to delete save\n", 31, 0);
        }
        else{
            colored_printS("Save does not exist\n", 31, 1);
        }
    }
    else{
        colored_printS("Exceed maximum number of save", 31, 1);
    }
}