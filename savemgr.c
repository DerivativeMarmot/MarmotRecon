#include "savemgr.h"

// option == true means new game, otherwise load a save
cJSON *saveSelector(bool option){
    int saveMax = 3;
    char *common_path = "savedata/save%d.txt";
    char *savepath;
    for (int i=1; i<=saveMax; ++i){

        size_t len = (size_t)snprintf(NULL, 0, common_path, i);
        savepath = malloc (sizeof(char) * (len+1));
        if (!savepath){
            perror("open a file");
            return NULL;
        }
        sprintf(savepath, common_path, i);
        savepath[len] = '\0';

        // 0 on success, -1 on fail
        if (access(savepath, R_OK) == 0){
            printf("save %d exists\n", i);
        }else{
            printf("save %d is empty\n", i);
        }
    }

    char c = input_c("Select a save");
    if (c >= '1' && c <= saveMax + 48){
        if (option){
            return userInit(savepath);
        }else{
            return userLoad(savepath);
        }
    }else{
        puts("No such file");
    }
}

cJSON *userInit(char *savepath){
    cJSON *user_json = cJSON_CreateObject();

    // create username
    char username[21];
    do{
        memset(username, 0, sizeof(username));
        if (input_s(username, 20, "Username (Maximum of 20 characters)")){
            printf("Please confirm your user name(y/n): %s", username);
            char c = input_c("\0");
            if (c == 'Y' || 'y'){
                puts("Username confirmed.");
                break;
            }else if (c == 'N' || 'n'){
                puts("Enter Username again.");
            }else{
                ;
            }
        }
    } while(1);
    cJSON_AddStringToObject(user_json, "name", username);

    // create position
    int pos[2] = {0, 0};
    cJSON_AddItemToObject(user_json, "position", cJSON_CreateIntArray(pos, 2));

    // create inv
    cJSON_AddItemToObject(user_json, "Inventory", cJSON_CreateObject());

    // wirte to file
    char *json2str = cJSON_Print(user_json);
    FILE *fp = fopen(savepath, "w");
    if (fp){
        fwrite(json2str, strlen(json2str), 1, fp);
    }else{
        perror("open a file");
    }

    free(json2str);
    fclose(fp);

    return user_json;
}

cJSON *userLoad(char *savepath){
    return file2Json(savepath);
}