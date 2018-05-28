//randomtestcard1.c
//Created by Shiyi Zhang
//This program is to random test card smithy

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
    //assign variables value
    int flag = 1;
    char testCard[] = "smithy";
    struct gameState testState, tempTestState;
    int a = 1000;
    int i, j, k;
    int returnVal;
    int handPos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;
    int currentPlayer;
    int addingCard = 3;
    int discardCount =1;
    int totalCards, tempTotalCards;

    srand(time(NULL));
    printf ("*************RANDOM TESTS FOR CARD %s**************\n", testCard);

    //get the random numbers for the testState struct
    for (i = 0; i < a; i++){
        for (j = 0; j < sizeof(struct gameState)/ sizeof(int); j++) {
            ((int*)&testState)[j] = rand() % 128;
        }
        testState.numPlayers = (rand() % 3)+2;
        testState.whoseTurn = rand() % testState.numPlayers;
        currentPlayer = whoseTurn(&testState);
        testState.handCount[currentPlayer] = (rand() % (MAX_HAND/2))+1;
        testState.deckCount[currentPlayer] = (rand() % (MAX_DECK/2))+1;
        testState.discardCount[currentPlayer] = (rand() % (MAX_DECK/2))+1;
        handPos = (rand() % testState.handCount[currentPlayer]);
        //copy testState struct to tempTestState for testing
        memcpy(&tempTestState, &testState, sizeof(struct gameState));
        //test return value
        returnVal = cardEffect(smithy, choice1, choice2, choice3, &tempTestState, handPos, &bonus);
        if (returnVal != 0) {
            printf("Failed on return value.");
            flag = 0;
        };

        //test hand count value
        if (tempTestState.handCount[currentPlayer] != testState.handCount[currentPlayer]-discardCount){
            flag = 0;
            printf("Hand count is %d, and the expected value is %d.\n", tempTestState.handCount[currentPlayer], testState.handCount[currentPlayer]-discardCount);
        }

        //test deck and discard count value
        totalCards = testState.deckCount[currentPlayer] + testState.discardCount[currentPlayer];
        tempTotalCards = tempTestState.deckCount[currentPlayer] + tempTestState.discardCount[currentPlayer];
        if (tempTotalCards != totalCards - addingCard) {
            flag = 0;
            printf("Total Cards are %d, and the expected value is %d.\n", tempTotalCards, totalCards-addingCard);
        };
  }
    //Final bool check to see whether testing passed or not
    if (flag) {
        printf("***********TEST SUCCEED************\n");
    } 
    else{
        printf("***********TEST FAILED***********\n");
    }

    return 0;
}