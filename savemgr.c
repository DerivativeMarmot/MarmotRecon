#include "savemgr.h"

// option == true means new game, otherwise load a save
cJSON *saveSelector(bool option){
    char *savepath;
    // prompt usable saves
    bool save_status[MAX_SAVE];
    for (int i=0; i<MAX_SAVE; ++i){
        
        // allocate string of savepath
        int len = snprintf(NULL, 0, COMMON_PATH, i) + strlen(USER_JSON);
        savepath = malloc (sizeof(char) * (len+1));
        if (!savepath){
            fprintf(stderr, "\033[;31mmalloc: failed to allocate mem\033[0m");
            exit(EXIT_FAILURE);
        }
        sprintf(savepath, COMMON_PATH, i);
        savepath[len] = '\0';

        // 0 on success, -1 on fail
        if (access(savepath, R_OK) == 0){
            printf("    %d. save %d exists\n", i, i);
            save_status[i] = true;
        }else{
            printf("    %d. save %d is empty\n", i, i);
            save_status[i] = false;
        }
    }
    puts("    q. Go back");

    // let user select a save
    char c = input_c("Select a save");
    if (c >= '0' && c < MAX_SAVE + 48){ // save0 ~ save9
        sprintf(savepath, COMMON_PATH, c-48);
        // new game
        if (option){
            // overwrite exsiting game
            if (save_status[c - 48]){
                char c = input_c("\033[0;33mThis is a existing save. Are you sure to overwrite it?\033[0m(y/n)"); // yellow
                while (1){
                    if (c == 'Y' || c == 'y')
                        puts("Save overwrited");
                    else if (c == 'N' || c == 'n')
                        puts("Operation cancelled.");
                    else
                        c = input_c("\0");
                }
            }
            mkdir(savepath, S_IRWXU); // 700
            return userInit(savepath);
        }else{
            strcat(savepath, USER_JSON);
            return userLoad(savepath);
        }
    }else if (c == 'q'){
        ;
    }else{
        puts("No such file");
    }

    free(savepath);
    return NULL;
}

cJSON *userInit(char *savepath){
    cJSON *user_json = cJSON_CreateObject();

    // create username
    char username[21];
    do{
        memset(username, 0, sizeof(username));
        if (input_s(username, 20, "Username (Maximum of 20 characters)")){
            printf("Please confirm your user name(y/n): %s\n", username);
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

    // create inv
    cJSON_AddItemToObject(user_json, "Inventory", cJSON_CreateObject());

    return user_json;
}

cJSON *userLoad(char *savepath){
    return file2Json(savepath);
}

void save2file(cJSON *json, mrMap *mymap){
    char *json2str = cJSON_Print(json);
    FILE *fp = fopen(cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(json, "savepath")), "w");
    if (fp){
        fwrite(json2str, strlen(json2str), 1, fp);
    }else{
        perror("open a file");
    }
    free(json2str);
    fclose(fp);
}