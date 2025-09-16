#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int upc;
    double price;
    char name[32];
} item;

int create_item(item *it, const char name[], int upc, double price) {
    it->upc = upc;
    it->price = price;
    strcpy(it->name, name);
    return 0;
}

item* get_item(item *items, const char *name, int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(items[i].name, name) == 0) {
            return &items[i];
        }
    }
    return NULL;
}


int main(void) {

    srand48((long)time(NULL));
    char text[4096];
    const char *itemNames[] = {
        "Apple",
        "Banana",
        "Carrot",
        "Donut",
        "Egg"
    };
    int countForSale = sizeof(itemNames) / sizeof(itemNames[0]);
    item *itemsForSale = malloc(countForSale * sizeof(item));

    
    strcat(text, "\033[2J\033[H");
    strcat(text, "Welcome to the store!\nWe have ");
    for (int i = 0; i < countForSale; i++) {
        create_item(&itemsForSale[i], itemNames[i], (int)drand48()*1e12, (drand48() + 0.2) * 10);
        char buffer[128];
        sprintf(buffer, "%s's", itemsForSale[i].name);
        strcat(text, buffer);
        if (i < countForSale - 2) {
            strcat(text, ", ");
        } else if(i < countForSale - 1){
            strcat(text, " and ");
        } else {
            strcat(text, ".\nEnter \"done\" to finish up!\n");
        }
    }
    strcat(text, "Enter items you wish to purchase:\n");
    printf("%s", text);
    char input[32];
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "done") == 0) {
            printf("%s", text);
            break;
        }
        for (int i = 0; input[i]; i++) {
            input[i] = tolower((unsigned char)input[i]);
        }
        input[0] = toupper((unsigned char)input[0]);

        item *found = get_item(itemsForSale, input, countForSale);

        char buffer[64];
        if (found) {
            sprintf(buffer, "Item: %s, Price: $%.2f\n", found->name, found->price);
        } else {
            sprintf(buffer, "Item not found.\n");
        }
        strcat(text, buffer);
        printf("%s", text);
    }
    
    free(itemsForSale);
    return 0;
}