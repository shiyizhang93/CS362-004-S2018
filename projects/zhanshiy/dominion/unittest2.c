//unitest2.c
//Created by Shiyi Zhang for Assignment 3
//It is to test the function isGameOver 
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

int main (int argc, char** argv) {
    struct gameState testState;
    int i;
    int pilesNumber = 25;
    int testVal;
    int expectedVal;

    //initiliaze each of the supply pile for only one card 
    //To easy test
    for (i = 0; i < pilesNumber; i++){
	    testState.supplyCount[i] = 1;
     }
    printf("Test suite for function isGameOver\n");
    
    printf("Test case 1: ");
    expectedVal = 0;
    testVal = isGameOver(&testState);
    printf("%s\n", (testVal == expectedVal) ? "PASS" : "FAIL");
    printf(" The function should return 0, because it still has a province card and no empty supply piles\n");

    printf("Test case 2: ");
    expectedVal = 1;
    testState.supplyCount[province] = 0;
    testVal = isGameOver(&testState);
    printf("%s\n", (testVal == expectedVal) ? "PASS" : "FAIL");
    printf(" The function should return 1, because it has no province card in supply piles\n");

    printf("Test case 3: ");
    expectedVal = 1;
    testState.supplyCount[province] = 1;
    testState.supplyCount[smithy] = testState.supplyCount[council_room] = testState.supplyCount[adventurer] = 0;
    testVal = isGameOver(&testState);
    printf("%s\n", (testVal == expectedVal) ? "PASS" : "FAIL");
    printf(" The function should return 1, because three of the supply piles (expcept province pile) become 0\n");

    return 0;
}