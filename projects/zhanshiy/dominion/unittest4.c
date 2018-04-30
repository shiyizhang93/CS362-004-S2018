//unitest4.c
//Created by Shiyi Zhang for Assignment 3
//It is to test the function scoreFor 
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <math.h>
#include "rngs.h"

struct scoreCardStr {
    int curse;
    int estate;
    int greatHall;
    int duchy;
    int province;
    int gardens;
};

struct gameState testGame(int randomSeed) {
    struct gameState testState;
    int k[10] = {adventurer, council_room, gardens, mine, remodel, smithy, baron, great_hall, steward, tribute};

    initializeGame(2, k, randomSeed, &testState);

    int money = 0;
    int i = 0;
    int smithyFlag = -1;
    int adventurerFlag = -1;
    int smithyCount = 0;
    int adventurerCount = 0;

    while (!isGameOver(&testState)){
	    money = 0;
	    smithyFlag = -1;
	    adventurerFlag = -1;
	    for (i = 0; i < numHandCards(&testState); i++) {
	      if (handCard(i, &testState) == copper)
		      money++;
	      else if (handCard(i, &testState) == silver)
		      money += 2;
	      else if (handCard(i, &testState) == gold)
		      money += 3;
	      else if (handCard(i, &testState) == smithy)
		      smithyFlag = i;
	      else if (handCard(i, &testState) == adventurer)
		      adventurerFlag = i;
	    }

  	  if (whoseTurn(&testState) == 0) {
  	    if (smithyFlag != -1) {
  		    playCard(smithyFlag, -1, -1, -1, &testState);
  		    money = 0;
  		    i=0;
  		    while(i<numHandCards(&testState)){
  		      if (handCard(i, &testState) == copper){
  			      playCard(i, -1, -1, -1, &testState);
  			      money++;
  		      }
  		      else if (handCard(i, &testState) == silver){
  			      playCard(i, -1, -1, -1, &testState);
  			      money = money + 2;
  		      }
  		      else if (handCard(i, &testState) == gold){
  			      playCard(i, -1, -1, -1, &testState);
  			      money = money + 3;
  		      }
  		    i++;
  		  }
      }
  	    if (money >= 8) {
  		    buyCard(province, &testState);
  	    }
  	    else if (money >= 6) {
  		    buyCard(gold, &testState);
  	    }
  	    else if ((money >= 4) && (smithyCount < 2)) {
  		    buyCard(smithy, &testState);
  	    	smithyCount++;
  	    }
  	    else if (money >= 3) {
  		    buyCard(silver, &testState);
  	    }
  	    endTurn(&testState);
    }
	  else {
	    if (adventurerFlag != -1) {
		    playCard(adventurerFlag, -1, -1, -1, &testState);
		    money = 0;
		    i=0;
		    while(i<numHandCards(&testState)){
		      if (handCard(i, &testState) == copper){
			      playCard(i, -1, -1, -1, &testState);
			      money++;
		      }
		      else if (handCard(i, &testState) == silver){
            playCard(i, -1, -1, -1, &testState);
			      money = money + 2;
		      }
		      else if (handCard(i, &testState) == gold){
			      playCard(i, -1, -1, -1, &testState);
			      money = money + 3;
		      }
	      i++;
		    }
     }
     if (money >= 8) {
		    buyCard(province, &testState);
     }
     else if ((money >= 6) && (adventurerCount < 2)) {
		    buyCard(adventurer, &testState);
		    adventurerCount++;
     }
     else if (money >= 6){
		    buyCard(gold, &testState);
     }
     else if (money >= 3){
		    buyCard(silver, &testState);
     }
     endTurn(&testState);
    }
   }
    return testState;
}

void cardCounts(int player, int cardNum, int cards[], struct scoreCardStr *deckPile) {
    int i;
    for (i = 0; i < cardNum; i++) {
	    switch (cards[i]) {
        case curse:
  		    deckPile->curse++;
  		  break;
  	    case estate:
  		    deckPile->estate++;
  		  break;
  	    case great_hall:
  		    deckPile->greatHall++;
  		  break;
  	    case duchy:
  	    	deckPile->duchy++;
  		  break;
  	    case province:
    		  deckPile->province++;
    		break;
  	    case gardens:
  		    deckPile->gardens++;
  		  break;
	}
    }
}

int calScore(int player, struct gameState *gameState) {
    int score = 0;
    struct scoreCardStr deckPile = {0, 0, 0, 0, 0, 0};

    cardCounts(player, gameState->handCount[player], gameState->hand[player], &deckPile);
    cardCounts(player, gameState->discardCount[player], gameState->discard[player], &deckPile);
    cardCounts(player, gameState->deckCount[player], gameState->deck[player], &deckPile);
    int scoreCards = deckPile.curse + deckPile.estate + deckPile.greatHall + deckPile.duchy + deckPile.province + deckPile.gardens;
    int gardenCounts = (int)floor((float)scoreCards / 10);

    score = score - (deckPile.curse);
    score = score + (deckPile.estate);
    score = score + (deckPile.greatHall);
    score = score + (deckPile.duchy * 3);
    score = score + (deckPile.province * 6);
    score = score + (deckPile.gardens * gardenCounts);
    
    return score;
}

int main (int argc, char** argv) {
    struct gameState testResult;
    int i;
    int randomSeed = 2;
    int expectedPlayer1, expectedPlayer2;
    int testPlayer1, testPlayer2; 

    testResult = testGame(randomSeed);

    printf("Test suite for function scoreFor\n");

    printf("Test Case 1: ");
    expectedPlayer1 = calScore(0, &testResult);
    expectedPlayer2 = calScore(1, &testResult);
    testPlayer1 = scoreFor(0, &testResult);
    testPlayer2 = scoreFor(1, &testResult);
    printf("%s", (expectedPlayer1 == testPlayer1 && expectedPlayer2 == testPlayer2) ? "PASS" : "FAIL");
    printf(" The score of expected player 1 is %d, but the actual score is %d.\n The score of expected player 2 is %d, but the actual score is %d\n", expectedPlayer1, testPlayer1, expectedPlayer2, testPlayer2);

    for (i = 0; i < testResult.handCount[0]; i++)
	    testResult.hand[0][i] = province;
    for (i = 0; i < testResult.discardCount[0]; i++)
	    testResult.discard[0][i] = estate;
    for (i = 0; i < testResult.deckCount[0]; i++)
	    if (i % 2 == 0) 
        testResult.deck[0][i] = duchy;
    	else 
        testResult.deck[0][i] = great_hall;

    printf("Test case 2: ");
    expectedPlayer1 = calScore(0, &testResult);
    expectedPlayer2 = calScore(1, &testResult);
    testPlayer1 = scoreFor(0, &testResult);
    testPlayer2 = scoreFor(1, &testResult);
    printf("%s", (expectedPlayer1 == testPlayer1 && expectedPlayer2 == testPlayer2) ? "PASS" : "FAIL");
    printf(" The score of expected player 1 is %d, but the actual score is %d.\n The score of expected player 2 is %d, but the actual score is %d\n",
	    expectedPlayer1, testPlayer1, expectedPlayer2, testPlayer2);

    return 0;
}
