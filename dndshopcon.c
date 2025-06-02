#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//For my DND Campaign, I need to constantly roll for shopkeepers. 
//Instead of doing that manually like a normal person, I decided to create this because I have mental issues.
int luckrecalc() { //recalculates luck so you can reuse this 
    return (rand() % 36) * 3;
}
int shopres() {
    int shops[5] = {10, 13, 11, 15, 2};
    int choiceshop = rand() % 5;
    int shopkeeper = shops[choiceshop];
    int resistance;

    if (shopkeeper < 10) {
        resistance = shopkeeper * 100;
    } else if (shopkeeper < 20) {
        resistance = shopkeeper * 500;
    } else if (shopkeeper < 30) {
        resistance = shopkeeper * 750;
    } else if (shopkeeper < 40) {
        resistance = shopkeeper * 900;
    } else {
        resistance = shopkeeper * 1000;
    }

    return resistance;
}
char* context() { //gets context, which is your place in the world. Note that chaotic/netural/lawful doesn't matter here, only Good/Neutral/Bad
    static char context[100];
    printf("Enter context for shopkeeper (Good, Neutral, Bad): ");
    if (fgets(context, sizeof(context), stdin) != NULL) {
        size_t len = strlen(context);
        if (len > 0 && context[len - 1] == '\n') {
            context[len - 1] = '\0'; 
        }
        return context;
    }
    return NULL;
}
int shopdndroll(int level, int bonus, int luck, char *context) { //main function 
    int successvalue = 1000;
    int luckval = 0;
    int contextval = 0;
    int resistance = shopres();
    if (luck % 2 == 0) {
        if (luck > 60) {
            luckval = 1000;
            luckrecalc();
        } else if (luck < 20) {
            luckval = -1000;
            luckrecalc();
        } else {
            luckrecalc();
        }
    }
    if (context == NULL) {
        printf("No context provided.\n");
        return -1; 
    } else if (strcmp(context, "Good") == 0) {
        contextval = 1000;
    } else if (strcmp(context, "Neutral") == 0) {
        contextval = 0;
    } else if (strcmp(context, "Bad") == 0) {
        contextval = -3000;
    }
    // successvalue is final returned value, this is used to determine success. 
    int bonusval = bonus * 500;
    int levelval = level * 1000;
    successvalue = levelval + bonusval + luckval + resistance + contextval;

    return successvalue;
}
int main() { //does the command things!
    srand(time(NULL)); 
    int level, bonus, luck;
    char *shop_context;
    printf("Enter level: ");
    scanf("%d", &level);
    printf("Enter bonus: ");
    scanf("%d", &bonus);
    printf("Enter luck: ");
    scanf("%d", &luck);
    getchar(); 
    shop_context = context();
    int successvalue = shopdndroll(level, bonus, luck, shop_context);
    printf("Success value: %d\n", successvalue);
    if (successvalue > 8000) {
        printf("You conned the DND shopkeeper!Great job! Now he's probably gonna be homeless!\n");
    } else if (successvalue > 7000) {
        printf("You didn't con the shopkeeper, but you got a decent deal.\n");
    } else if (successvalue > 6000) {
        printf("The shopkeeper is not happy. Upcharge!\n");
    } else {
        printf("ok ur getting kicked out bruh\n");
        //When this code is complete, it will change the shopkeeper's inventory to be more expensive, or give you a discount.
    }
    return 0;
}
