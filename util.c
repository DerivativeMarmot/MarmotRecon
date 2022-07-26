#include "util.h"

cJSON *file2Json(char *filename)
{
    if (access(filename, R_OK) == -1)
        printf("\033[;31mACCESS\033[0m: No such file %s", filename);
    else
    {
        FILE *fp = fopen(filename, "r");
        if (fp)
        {
            int length;
            fseek(fp, 0, SEEK_END);
            length = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            char buffer[length + 1];
            fread(buffer, 1, length, fp);
            fclose(fp);
            buffer[length] = '\0';

            return cJSON_Parse(buffer);
        }
        else
        {
            fprintf(stderr, "failed to open %s", filename);
            exit(EXIT_FAILURE);
        }
    }
    return NULL;
}

char input_c(char *prompt){
    if (strcmp(prompt, "\0") == 0){
        printf("> ");
    }else{
        printf("%s\n> ", prompt);
    }
    char c = getchar(); // get the first char from input
    while (getchar() != '\n') ; // drop the rest of char
    return c;
}

char *input_s(char *st, int n, char* prompt)
{
    if (strcmp(prompt, "\0") == 0){
        printf("> ");
    }else{
        printf("%s\n> ", prompt);
    }
    int i = 0;
    char *ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\0' && st[i] != '\n')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n') ;
    }
    return ret_val;
}

void colored_printC(char prompt, int color, int option){
    if (color >= 31 && color <= 36 || color >= 41 && color <= 46)
        printf("\033[%d;%dm%c\033[0m", option, color, prompt);
    else
        putchar(prompt);
}

void colored_printS(char *prompt, int color, int option){
    if (color >= 31 && color <= 36 || color >= 41 && color <= 46)
        printf("\033[%d;%dm%s\033[0m", option, color, prompt);
    else
        puts(prompt);
}

int gen_randomInt(int min, int max){
    return rand() % (max - min) + min;
}

double gen_randomDouble(double min, double max){
    if (min + 0.01 >= max)
        return min;
    return rand() % (int)((max- min) * 100 ) / 100.0 + min;
}

char weighted_randC(char *sample, int *weight, int count){
    int r = rand() % 101;
    int wR = 0;
    for (int i = 0; i<count; ++i){
        wR += weight[i];
        if (wR >= r){
            return sample[i];
        }
    }
    return '0';
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

int weighted_rand2DA(int *weight, int count){
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

void weighted_rand3DA(char *(*sample)[3], double *weight, int *shape, char *target){
    puts(sample[rand() % shape[0]][rand() % shape[1]]);
    int r = rand() % 101;
    printf("r= %d\n", r);
    int wR = 0;
    for (int row = 0; row < shape[0]; ++row){
        wR += weight[row];
        if (wR >= r){
            int col = rand() % shape[1];
            //puts(sample[row][col]);
            memcpy(target, sample[row][col], strlen(sample[row][col]) + 1);
            break;
        }
    }
}

//void colored_print()


/*int main(void){
    cJSON *json = file2Json("CharaAttr.json");
    puts(cJSON_Print(json));
    return 0;
}*/