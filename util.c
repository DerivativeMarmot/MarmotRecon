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

char input(char *prompt){
    printf("%s", prompt);
    char c = getchar(); // get the first char from input
    while (getchar() != '\n') ; // drop the rest of char
    return c;
}

//void colored_print()


/*int main(void){
    cJSON *json = file2Json("CharaAttr.json");
    puts(cJSON_Print(json));
    return 0;
}*/