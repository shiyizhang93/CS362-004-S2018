//cardtest1.c
//Created by Shiyi Zhang for Assignment 3
//It is to test the adventurer card effect

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

void showTestResult(int expectedVal, int testVal, char *temp) {
    char *testName = temp;
    if (expectedVal == testVal) {
	    printf("PASS: %s", testName);
    } 
    else {
	    printf("FAIL: %s - expected value is %d, but the actual value is %d", testName, expectedVal, testVal);
    }
    printf("\n");
}

int main (int argc, char** argv) {
    struct gameState startState; 
    struct gameState endState;
    int numPlayers = 2;
    int handFlag = 0;
    int choice1 = -1;
    int choice2 = -1;
    int choice3 = -1;
    int bonus = 0;
    int seed = 10;
    int k[10] = {adventurer, council_room, gardens, mine, remodel, smithy, baron, great_hall, steward, village};
    int i;
    int expectedVal;
    int testVal;
    int tempFlag = 0;
    int numNewCardHand = 2;
    int numCardPlay = 1;
    int playerNum;

    initializeGame(numPlayers, k, seed, &startState);
    endState = startState;
    printf("Test suite for card adventurer effect\n");
    for (playerNum = 0; playerNum < numPlayers; playerNum++) {
	    cardEffect(adventurer, choice1, choice2, choice3, &endState, handFlag, &bonus);
      printf("Test result for player %d\n", playerNum+1);
    	expectedVal = startState.handCount[playerNum] + numNewCardHand - numCardPlay;
    	testVal = endState.handCount[playerNum];
    	showTestResult(expectedVal, testVal, "Player hand number");
    
    	expectedVal = startState.playedCardCount + numCardPlay;
    	testVal = endState.playedCardCount;
    	showTestResult(expectedVal, testVal, "Player played card number");
    
    	expectedVal = playerNum == 1 ? 
    	    startState.deckCount[1-playerNum] - numNewCardHand : startState.deckCount[1-playerNum];
    	testVal = endState.deckCount[1-playerNum];
    	showTestResult(expectedVal, testVal, "The other player deck number");
    
    	expectedVal = startState.coins;
    	testVal = endState.coins;
    	showTestResult(expectedVal, testVal, "Coin number");

    	expectedVal = numNewCardHand + startState.handCount[playerNum] - numCardPlay;
    	endTurn(&endState);
    	endTurn(&startState);
    	testVal = endState.discardCount[playerNum];
    	showTestResult(expectedVal, testVal, "Player discard number");

    	for (i = 0; i < treasure_map + 1; i++) {
    	    if (startState.supplyCount[i] != endState.supplyCount[i]) {
    		    tempFlag = 1;
    		  break;
    	    }
    	}
    	if (!tempFlag) {
    	    printf("PASS: The number of supply matches\n");
    	} 
      else {
    	    printf("FAIL: The number of supply does not match %d\n", i);
    	}
    }
    return 0;
}