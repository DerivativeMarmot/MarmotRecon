#include "map.h"
//#include "util.h"

int gen_ran_bet(int min, int max){
    return rand() % (max - min) + min;
}

void map_init(mrMap *myMap){
    int HEIGHT_MIN = 6;
    int HEIGHT_MAX = 10;
    int WIDTH_MIN = 16;
    int WIDTH_MAX = 23;
    int height = gen_ran_bet(HEIGHT_MIN, HEIGHT_MAX);
    //printf("%d\n", height);

    myMap->shape = (int *) malloc (sizeof(int) * (height + 1));
    myMap->map_clear = (char**) malloc (sizeof(char*) * height);
    myMap->map_bool = (char**) malloc (sizeof(char*) * height);

    // the number of rows
    myMap->shape[0] = height;
    //printf(" %d\n", height);

    for (int i=0; i<height; ++i){
        int width = gen_ran_bet(WIDTH_MIN, WIDTH_MAX); // random width between 6 ~ 9
        // the length of current row
        myMap->shape[i+1] = width;
        
        myMap->map_clear[i] = (char*)malloc(sizeof(char) * (width + 1));
        myMap->map_bool[i] = (char*)malloc(sizeof(char) * (width));

        // initialize all position to false (unvisited)
        memset(myMap->map_bool[i], '0', sizeof(char) * width);

        // initialize each position
        for (int j = 0; j<width; ++j){
            int r = rand() % 100;
            if (r < 10){ // 10%
                myMap->map_clear[i][j] = 'E'; // enemy
            }
            else if (r < 30){ // 20%
                myMap->map_clear[i][j] = 'M'; // mineral
            }
            else{ // 70%
                myMap->map_clear[i][j] = '*'; // null
            }
        }
        myMap->map_clear[i][width] = '\0';
        myMap->map_bool[i][width] = '\0';
    }
}

void map_print(mrMap *myMap, int *pos)
{
    for (int i = 0; i < (myMap->shape[0]); ++i)
    {
        for (int j = 0; j < (myMap->shape[i + 1]); ++j)
        {
            if (i == pos[0] && j == pos[1])
                colored_printC('#', 5);
            else if (myMap->map_bool[i][j] == '1')
                putchar(myMap->map_clear[i][j]);
            else
                putchar('*');
            putchar(' ');
        }
        putchar(10);
    }
}

cJSON *map_write(mrMap *myMap){
    cJSON *map_json = cJSON_CreateObject();
    cJSON_AddItemToObject(map_json, "shape", cJSON_CreateIntArray(myMap->shape, myMap->shape[0] + 1));
    cJSON_AddItemToObject(map_json, "clear", cJSON_CreateStringArray(myMap->map_clear, myMap->shape[0]));
    cJSON_AddItemToObject(map_json, "bool", cJSON_CreateStringArray(myMap->map_bool, myMap->shape[0]));
    
    return map_json;
}

void map_load(mrMap *myMap, cJSON *json_map){
    cJSON *json_shape = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json_map, "shape"), 0);
    cJSON *json_clear = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json_map, "clear"), 0);
    cJSON *json_bool = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json_map, "bool"), 0);
    
    int height = cJSON_GetNumberValue(json_shape);
    
    myMap->shape = malloc (sizeof(int) * (height + 1));

    myMap->map_clear = (char**) malloc (sizeof(char*) * height);
    myMap->map_bool = (char**) malloc (sizeof(char*) * height);

    // myMap->shape[0] = height
    myMap->shape[0] = height;

    // load json into struct
    for (int i=0; i<height; ++i){
        json_shape = json_shape->next;
        int width = cJSON_GetNumberValue(json_shape);
        myMap->map_clear[i] = (char*)malloc(sizeof(char) * (width + 1));
        myMap->map_bool[i] = (char*)malloc(sizeof(char) * (width + 1));

        /*char *temp_clear = cJSON_GetStringValue(json_clear);
        char *temp_bool = cJSON_GetStringValue(json_bool);
        for (int j = 0; j<width; ++j){
            myMap->map_clear[i][j] = temp_clear[j];
            myMap->map_bool[i][j] = temp_bool[j];
        }
        myMap->map_clear[width] = '\0';
        myMap->map_bool[width] = '\0';
        puts(myMap->map_clear[i]);
        puts(myMap->map_bool[i]);*/
        strncpy(myMap->map_clear[i], cJSON_GetStringValue(json_clear), width);
        myMap->map_clear[i][width] = '\0';
        strncpy(myMap->map_bool[i], cJSON_GetStringValue(json_bool), width);
        myMap->map_bool[i][width] = '\0';

        myMap->shape[i+1] = width;
        json_clear = json_clear->next;
        json_bool = json_bool->next;
    }
}

void map_free(int *shape, char **map_clear, char **map_bool){
    for (int i=0; i<shape[0]; ++i){
        free(map_clear[i]);
        free(map_bool[i]);
    }
    free(map_clear);
    free(map_bool);
    free(shape);
}

void mrMapMenu(){
    puts("\n\
    w: go up\n\
    s: go down\n\
    a: go left\n\
    d: go right\
    q: quit\n\
    ");
}

/*int main(void){
    marmotRecon *myMR;
    myMR->myMap = (mrMap*) malloc (sizeof(mrMap));
    myMR->myChara = (mrChara*) malloc (sizeof(mrChara));
    srand((unsigned)time(NULL));
    
    mrMap_gen_raw(myMR->myMap);
    mrMap_print(myMR->myMap);
    return 0;
}*/