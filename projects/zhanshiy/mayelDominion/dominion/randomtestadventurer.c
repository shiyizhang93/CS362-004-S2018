//randomtestadventurer.c
//created by Shiyi Zhang
//This program is to random test card adventurer

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
    char testCard[] = "adventurer";
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
    int addingCard = 2;
    int money, tempMoney;
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
        for (j = 0; j < testState.handCount[currentPlayer]; j++) {
            k = (rand() % 2);
            if (k == 0) {
                testState.hand[currentPlayer][j] = copper;
            } 
            else {
                testState.hand[currentPlayer][j] = estate;
            }
        }
        for (j = 0; j < testState.deckCount[currentPlayer]; j++) {
            k = (rand() % 2);
            if (k == 0) {
                testState.deck[currentPlayer][j] = copper;
            } 
            else {
                testState.deck[currentPlayer][j] = estate;
            }
        }

        //copy testState struct to tempTestState for testing
        memcpy(&tempTestState, &testState, sizeof(struct gameState));
        //test return value
        returnVal = cardEffect(adventurer, choice1, choice2, choice3, &tempTestState, handPos, &bonus);
        if (returnVal != 0) {
            printf("Failed on return value.");
            flag = 0;
        };

        //test hand count value
        if (tempTestState.handCount[currentPlayer] != testState.handCount[currentPlayer]+addingCard){
            flag = 0;
            printf("Hand count is %d, and the expected value is %d.\n", tempTestState.handCount[currentPlayer], testState.handCount[currentPlayer]+addingCard);
        }

        //test deck and discard count value
        totalCards = testState.deckCount[currentPlayer] + testState.discardCount[currentPlayer];
        tempTotalCards = tempTestState.deckCount[currentPlayer] + tempTestState.discardCount[currentPlayer];
        if (tempTotalCards != totalCards - addingCard) {
            flag = 0;
            printf("Total Cards are %d, and the expected value is %d.\n", tempTotalCards, totalCards-addingCard);
        };

        //test money count value
        money = 0;
        j = 0;
        while (j < numHandCards(&testState)) {
            if (handCard(j, &testState) == copper) {
                money++;
            } 
            else if (handCard(j, &testState) == silver) {
                money += 2;
            } 
            else if (handCard(j, &testState) == gold) {
                money += 3;
            }
            j++;
        }

        tempMoney = 0;
        j = 0;
        while (j < numHandCards(&tempTestState)) {
            if (handCard(j, &tempTestState) == copper) {
                tempMoney++;
            } 
            else if (handCard(j, &tempTestState) == silver) {
                tempMoney += 2;
            } 
            else if (handCard(j, &tempTestState) == gold) {
                tempMoney += 3;
            }
            j++;
        };
        if (tempMoney < money+2) {
            flag = 0;
            printf("Money Count is %d, and the expected Money Count is >= %d.\n", tempMoney, money+2);
        }
    }
    //Final bool check to see whether testing passed or not
    if (flag) {
        printf("***********TEST SUCCEED************\n");
    } 
    else{
        printf("***********TEST FAILED***********\n");
    }

    return 0;
};