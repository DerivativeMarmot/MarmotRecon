#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double randomDouble(double min, double max){
    if (min + 0.01 >= max)
        return min;
    return rand() % (int)((max- min) * 100 ) / 100.0 + min;
}

void colored_printS(char *prompt, int color){
    switch (color)
    {
    case 0:
        printf("\033[;32m%s\033[0m", prompt);
        break;
    case 1:
        printf("\033[;33m%s\033[0m", prompt);
        break;
    case 2:
        printf("\033[;31m%s\033[0m", prompt);
        break;
    case 3:
        printf("\033[;34m%s\033[0m", prompt);
        break;
    case 4:
        printf("\033[;35m%s\033[0m", prompt);
        break;
    case 5:
        printf("\033[;36m%s\033[0m", prompt);
        break;
    default:
        puts(prompt);
        break;
    }    
}

int main()
{
    
    return 0;
}