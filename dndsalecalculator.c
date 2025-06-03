#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
#include <math.h>
char* exampleinventory(int itemnumba, int* prices); // Not sure why, but the code didn't really work without initializing the char.
char* exampleinventory(int itemnumba,int* prices) { //I'm planning to make a database for this eventually, but for now this works.
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
        snprintf(itemgenerated, sizeof(itemgenerated), "%s of %s,costs %d.", initialitem[randomitemnum], itemtype[randomitemtype],prices[i]);
        //had to learn this, it was fun!  
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
    shopsway = ((charismaval * randshopsway) / 3 + (2*charismaval)/3);
    if (shopsway < 4) {
        printf("Get out of my store!\n");
        printf("You got kicked out of the store...\n"); //yeah pack it up 
        exit(0);
    } else if (shopsway >= 4 && shopsway <= 14) {
        printf("Sorry, but I'm not interested.\n");
        bonus = 0;
        return bonus;
    } else if (shopsway >= 15 && randshopsway < 20) {
        bonus = rand() % 6 + 5;
        printf("You get a sale! Bonus value: %d\n", bonus);
        return bonus;
    } else if (shopsway >= 20) {
        printf("MAX BONUS");
        bonus = 15;
        return bonus = 15;
    } else {
        printf("Incorrect charisma value dude, it's below 5\n");
        return -1; //It's the plus or minus charisma, not the actual charisma, since yes that's usually around 15.
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
    int prices;
    int* calculatedPrice= malloc(itemnumba * sizeof(int));   
    if (!calculatedPrice) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < itemnumba; i++) {
        prices = rand() % 2000 + 1000; // Generates a random price for each item
        calculatedPrice[i] = prices - (prices * salepercent / 500); // Calculates the final price after sale
    }
    return calculatedPrice;
}

int pricecalc(int* prices, int itemnumba, int salepercent) { //fun concept to buy the whole store. 
    //I'm planning on going all in on a big project that will involve combining all the shop code together.
    //Then, using the amount of money on hand aswell, and actually subtracting away from that etc etc.
    int price = 0;
    int finalprice = 0;
    int storecost = rand() % 1000 + 500;
    for (int i = 0; i < itemnumba; i++) {
        price += prices[i];
    }
    if (salepercent == 1) { // No discount!
        printf("Store Price: %d\n", price + storecost);
    } else {
        finalprice = price - (price * salepercent / 500);
        printf("Store Price: %d\n", finalprice + storecost);
    }
    return finalprice;
}

int main() {
    int charismaval, itemnumba, finalprice, salepercent,priceval,calculatedPrice; 
    int pricetotal[21];
    int bonus = 0;
    srand(time(NULL));
    printf("Welcome to the DnD Sale Calculator!\n");
    printf("Please enter your charisma value (-4 to 4):\n");
    scanf("%d", &charismaval);
    if (charismaval < -4 || charismaval > 4) {
        printf("nah lock in dude bruh\n");
        exit(1);
    }
    charismaval = charismaval + 4;
    bonus = shopbonuscalc(charismaval);
    salepercent = salecalc(bonus);
    printf("How many items do you want to create? Max of 20 items.\n");
    scanf("%d", &itemnumba);
    if (itemnumba <= 0 || itemnumba > 20) {
        printf("nah bruh the number of items was listed lock up twin\n");
        exit(0);
    }
    int* prices = generatePrices(itemnumba, salepercent);
    finalprice = pricecalc(prices, itemnumba, bonus);
    char* result = exampleinventory(itemnumba,prices);
    free(result);
    free(prices);
    return 0;
}
