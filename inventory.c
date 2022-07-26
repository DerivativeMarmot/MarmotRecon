#include "inventory.h"

void inv_print(cJSON *json)
{
    /*// puts(json->child->next->string);
    cJSON *pos_obj = cJSON_GetObjectItemCaseSensitive(json, "position");
    // puts(cJSON_Print(pos_obj));
    cJSON *arr_obj_0 = cJSON_GetArrayItem(pos_obj, 0);
    cJSON *arr_obj_1 = cJSON_GetArrayItem(pos_obj, 1);
    printf("%d %d\n", arr_obj_0->valueint, arr_obj_1->valueint);
    printf("%d %d\n", pos_obj->child->valueint, pos_obj->child->next->valueint);

    cJSON *inv_obj = cJSON_GetObjectItemCaseSensitive(json, "Inventory");
    // puts(cJSON_Print(inv_obj));
    printf("gold: %d\n", inv_obj->child->next->valueint);*/
    cJSON *item = json->child;
    while (item != NULL){
        printf("%s %d\n", item->string, item->valueint);
        item = item->next;
    }
}

void inv_addItem(cJSON *json, char* itemName, int amount){
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, itemName);
    if (item == NULL)
        cJSON_AddNumberToObject(json, itemName, amount);
    else{
        cJSON_SetNumberHelper(item, item->valueint + amount);
    }
}

void inv_subItem(cJSON *json, char* itemName, int amount){
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, itemName);
    if (item == NULL)
        printf("Item not found\n");
        //cJSON_AddItemToObject(json, itemName, cJSON_CreateNumber(amount));
    else{
        if (item->valueint > amount)
            cJSON_SetNumberHelper(item, item->valueint + amount);
        else
            printf("No enough item\n");
    }
}

void inv_deleteItem(cJSON *json, char* itemName){
    cJSON_DeleteItemFromObjectCaseSensitive(json, itemName);
}

void inv_menu(){
    puts("\n\
    1. \
    ");
}