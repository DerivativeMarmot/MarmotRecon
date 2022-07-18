#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double randomDouble(double min, double max){
    if (min + 0.01 >= max)
        return min;
    return rand() % (int)((max- min) * 100 ) / 100.0 + min;
}

int main()
{
    srand((unsigned)time(NULL));
    printf("%.2f\n", randomDouble(1.34, 20.55));
    printf("%.2f\n", randomDouble(1.34, 20.55));
    printf("%.2f\n", randomDouble(13.34, 20.55));
    printf("%.2f\n", randomDouble(13.34, 17.19));
    printf("%.2f\n", randomDouble(13.34, 15.01));
    printf("%.2f\n", randomDouble(14.34, 14.34));
    printf("%.2f\n", randomDouble(14.34, 14.35));
    if ((14.35 - 14.33) * 100 < 1){
        puts("what the hell");
    }
    return 0;
}