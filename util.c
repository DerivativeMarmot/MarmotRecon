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

// 0:green, 1: yellow, 2: red
// 3: blue, 4: Magenta, 5: Cyan
void colored_printC(char prompt, int color){
    switch (color)
    {
    case 0:
        printf("\033[;32m%c\033[0m", prompt);
        break;
    case 1:
        printf("\033[;33m%c\033[0m", prompt);
        break;
    case 2:
        printf("\033[;31m%c\033[0m", prompt);
        break;
    case 3:
        printf("\033[;34m%c\033[0m", prompt);
        break;
    case 4:
        printf("\033[;35m%c\033[0m", prompt);
        break;
    case 5:
        printf("\033[;36m%c\033[0m", prompt);
        break;
    default:
        putchar(prompt);
        break;
    }    
}

// 0:green, 1: yellow, 2: red
// 3: blue, 4: Magenta, 5: Cyan
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

int gen_randomInt(int min, int max){
    return rand() % (max - min) + min;
}

double gen_randomDouble(double min, double max){
    if (min + 0.01 >= max)
        return min;
    return rand() % (int)((max- min) * 100 ) / 100.0 + min;
}

//void colored_print()


/*int main(void){
    cJSON *json = file2Json("CharaAttr.json");
    puts(cJSON_Print(json));
    return 0;
}*/