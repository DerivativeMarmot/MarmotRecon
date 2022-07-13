#include "map.h"
//#include "util.h"

int gen_ran_bet(int min, int max){
    return rand() % (max - min) + min;
}

void mrMap_gen_raw(mrMap *myMap){
    int HEIGHT_MIN = 6;
    int HEIGHT_MAX = 10;
    int WIDTH_MIN = 16;
    int WIDTH_MAX = 23;
    int height = gen_ran_bet(HEIGHT_MIN, HEIGHT_MAX);
    //printf("%d\n", height);

    myMap->shape = (int *) malloc (sizeof(int) * (height + 1));
    myMap->map_clear = (char**) malloc (sizeof(char*) * height);
    myMap->map_bool = (bool**) malloc (sizeof(bool*) * height);

    // the number of rows
    myMap->shape[0] = height;
    //printf(" %d\n", height);

    for (int i=0; i<height; ++i){
        int width = gen_ran_bet(WIDTH_MIN, WIDTH_MAX); // random width between 6 ~ 9
        // the length of current row
        myMap->shape[i+1] = width;
        
        myMap->map_clear[i] = (char*)malloc(sizeof(char) * (width + 1));
        myMap->map_bool[i] = (bool*)malloc(sizeof(bool) * (width));

        // initialize all position to false (unvisited)
        memset(myMap->map_bool[i], false, sizeof(bool) * width);

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
    }
}

void mrMap_print(mrMap *myMap, int *pos)
{
    for (int i = 0; i < (myMap->shape[0]); ++i)
    {
        for (int j = 0; j < (myMap->shape[i + 1]); ++j)
        {
            
            if (i == pos[0] && j == pos[1])
                putchar('#');
            else if (myMap->map_bool[i][j])
                putchar(myMap->map_clear[i][j]);
            else
                putchar('*');
            putchar(' ');
        }
        putchar(10);
    }
}

void mrMap_menu(){
    puts("\n\
    w: go up\n\
    s: go down\n\
    a: go left\n\
    d: go right\
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