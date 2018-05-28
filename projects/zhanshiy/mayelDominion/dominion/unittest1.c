//unitest1.c
//Created by Shiyi Zhang for Assignment 3
//It is to test the function updataCoins
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

int main(int argc, char** argv){
    struct gameState testState;
    int numPlayers = 2;
    int playersNum = 0;
    int selectSeed = 10;
    int k[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};
    int bonus = 0;
    int testVal;
    int expectedVal;

    //initialze the game
    initializeGame(numPlayers, k, selectSeed, &testState);
    printf("Test suite for function updateCoins\n");
    printf("Test case 1: ");
    expectedVal = 4;
    updateCoins(playersNum, &testState, bonus);
    testVal = testState.coins;
    printf("%s\n", (testVal == expectedVal) ? "PASS" : "FAIL");
    printf("There should be 4 coins for player in first hand\n");
    
    //Player now have 1 gold, 1 silver, 2 copper and 1 bonus
    testState.hand[playersNum][0] = gold;
    testState.hand[playersNum][1] = silver;
    bonus = 1;
    printf("Test case 2: ");
    expectedVal = 8;
    updateCoins(playersNum, &testState, bonus);
    testVal = testState.coins;
    printf("%s\n", (testVal == expectedVal) ? "PASS" : "FAIL");
    printf(" There should be 8 coins for player in second hand\n");
    return 0;
}