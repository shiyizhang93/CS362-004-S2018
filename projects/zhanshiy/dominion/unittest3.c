//unittest.c
//Created by Shiyi Zhang for Assignment 3
//It is to test the function getCost 
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"


int main (int argc, char** argv) {
    //card cost form refer to http://wiki.dominionstrategy.com/index.php/List_of_cards
    int cardsCost[] = { 0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4 };
    int i;
    int expectedVal;
    int testVal;
    int cardsCount = treasure_map + 1;
    int tempFlag = 0;

    //Use the above reference to test the function getCost
    printf("Test suite for function getCost\n");
    for (i = 0; i < cardsCount; i++) {
	    testVal = getCost(i);
	    expectedVal = cardsCost[i];
	    if (expectedVal != testVal) {
	        tempFlag = 1;
	        break;
	    }
    }
    //Test Case 1
    if (tempFlag) {
	    printf("Test case 1: FAIL for card index %d. The expected value is %d, but test value is %d\n", i, expectedVal, testVal);
    } 
    else {
	    printf("Test case 1: PASS the test case 1\n");
    }
    //Test Case 2
    i = 77;
    testVal = getCost(i);
    expectedVal = -1;
    if (expectedVal != testVal) {
	    printf("Test case 2: FAIL for invalid card index %d. The expected value is %d, but test value is %d\n", i, expectedVal, testVal);
    } 
    else {
	    printf("Test case 2: PASS the test case 2\n");
    }

    return 0;
}