#include "util.h"

cJSON *file2Json(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp)
    {
        int length;
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        printf("%d\n", length);
        fseek(fp, 0, SEEK_SET);
        char buffer [length + 1];
        fread(buffer, 1, length, fp);
        fclose(fp);
        buffer[length] = '\0';
        //puts(buffer);

        return cJSON_Parse(buffer);
    }
    else{
        char buffer[40];
        sprintf(buffer, "failed to open %s", filename);
        perror(buffer);
        return NULL;
    }
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


//void colored_print()


/*int main(void){
    cJSON *json = file2Json("CharaAttr.json");
    puts(cJSON_Print(json));
    return 0;
}*/