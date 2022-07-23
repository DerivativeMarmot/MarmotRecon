#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double randomDouble(double min, double max){
    if (min + 0.01 >= max)
        return min;
    return rand() % (int)((max- min) * 100 ) / 100.0 + min;
}

void colored_printS(char *prompt, int color, int option){
    if (color >= 31 && color <= 36 || color >= 41 && color <= 46)
        printf("\033[%d;%dm%s\033[0m", option, color, prompt);
    else
        puts(prompt);
}

int weighted_randA(int *weight, int count){
    int r = rand() % 101;
    printf("r= %d\n", r);
    int wR = 0;
    for (int i = 0; i<count; ++i){
        wR += weight[i];
        if (wR >= r){
            return i;
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));
    //colored_printS("hello\n", 31, 10);
    //printf("hello\n");  
    int count = 3;
    char *sample[] = {"bronze", "iron", "gold"};
    int weight[] = {50, 40, 10};
    int index = weighted_randA(weight, count);
    puts(sample[index]);
    return 0;   
}