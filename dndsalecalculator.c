#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
//wip it's broken right now, and I'm fixing it asap!
char* exampleinventory(int itemnumba);

char* exampleinventory(int itemnumba) {
    char initialitem[][20] = {"Boots", "Sword", "Shield", "Potion", "Helmet", "Armor", "Bow", "Arrow", "Ring", "Amulet"}; // Items that can be generated
    char itemtype[][20] = {"Greed", "Generosity", "Kindness", "Courage", "Wisdom", "Justice", "Humility", "Patience", "Honesty", "Loyalty"}; //Types of items
    int itemcount = sizeof(initialitem) / sizeof(initialitem[0]);
    int itemtypecount = sizeof(itemtype) / sizeof(itemtype[0]);
    char* result = malloc(itemnumba * 100 * sizeof(char));
    if (!result) {
        printf("no memory .boo. go home.\n");
        return NULL;
    }
    strcpy(result, "Generated Items:\n");
    for (int i = 0; i < itemnumba; i++) {
        int randomitemnum = rand() % itemcount;
        int randomitemtype = rand() % itemtypecount;
        char itemgenerated[100];
        snprintf(itemgenerated, sizeof(itemgenerated), "%s of %s", initialitem[randomitemnum], itemtype[randomitemtype]);
        //had to learn this, it was fun! 
        //i've been on my computer for 7 hours straight now :( 
        strcat(result, itemgenerated);
        strcat(result, "\n");
    }
    return result;
}

int shopbonuscalc(int charismaval) {
    int randshopsway = 0;
    int shopsway = 0;
    int bonus = 0;
    randshopsway = ((rand() % 20)); // Random generation of "sway" of shopkeeper to you or agaisnt you. Or he just hates you.
    shopsway = ((charismaval * randshopsway) / 3 + charismaval);
    printf("Current shopsway value: %d\n", shopsway);
    if (shopsway < 4) {
        printf("Get out of my store!\n");
        printf("You got kicked out of the store...\n"); //yeah pack it up 
        exit(0);
    } else if (shopsway >= 4 && shopsway <= 14) {
        printf("Sorry, but I'm not interested.\n");
        bonus = 0;
        printf("%d\n", bonus);
        return bonus;
    } else if (shopsway > 15 && randshopsway < 20) {
        bonus = rand() % 6 + 5;
        printf("You get a sale! Bonus value: %d\n", bonus);
        return bonus;
    } else if (shopsway >= 20) {
        printf("MAX BONUS");
        bonus = 15;
        return bonus = 15;
    } else {
        printf("Incorrect charisma value dude, it's below 5\n");
        return -1; // Error case
    }
    return 0;
}

int salecalc(int bonus) {
    float salepercent = 0;
    if (bonus < 5) {
        printf("You were unable to haggle for a sale.\n");
        return 1;
    } else {
        salepercent = ((int)bonus) * (rand() % 5 + 1);
        printf("You got a sale of %f percent!\n", salepercent);
        return salepercent;
    }
}

int* generatePrices(int itemnumba, int salepercent) {
    int* prices = malloc(itemnumba * sizeof(int));
    if (!prices) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < itemnumba; i++) {
        prices[i] = rand() % 2000 + 1000; // Generate random price for each item
        int finalPrice = prices[i] - (prices[i] * salepercent / 500); // Calculate final price after sale
        printf("Item %d price: %d\n", i + 1, finalPrice);
    }
    return prices;
}

int pricecalc(int* prices, int itemnumba, int salepercent) {
    int price = 0;
    int finalprice = 0;
    for (int i = 0; i < itemnumba; i++) {
        price += prices[i];
    }
    if (salepercent == 1) { // No discount!
        printf("Final price: %d\n", price);
    } else {
        finalprice = price - (price * salepercent / 500);
        printf("Final price: %d\n", finalprice);
    }
    return finalprice;
}

int main() {
    int charismaval, itemnumba, finalprice, salepercent;
    int bonus = 0;
    srand(time(NULL));
    printf("Welcome to the DnD Sale Calculator!\n");
    printf("Please enter your charisma value (-4 to 4):\n");
    scanf("%d", &charismaval);
    bonus = shopbonuscalc(charismaval);
    printf("Shop bonus: %d\n", bonus);
    salepercent = salecalc(bonus);
    printf("How many items do you want to create? Max of 20 items.\n");
    scanf("%d", &itemnumba);
    if (itemnumba <= 0 || itemnumba > 20) {
        printf("nah bruh the number of items was listed lock up twin\n");
        return 1;
    }
    int* prices = generatePrices(itemnumba, salepercent);
    finalprice = pricecalc(prices, itemnumba, bonus);
    char* result = exampleinventory(itemnumba);
    
    if (result) {
        printf("%s", result);
        free(result); // Free my boy memory
    }
    return 0;
}
