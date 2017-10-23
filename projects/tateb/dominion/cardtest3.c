/*************************************************************
 * File: cardtest3.c
 * Purpose: Unit test for the village dominion card
 *************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pass = 1;

void myAssert(int actual, int expected, char* message) {
	if (actual == expected) {
		printf("SUCCESS: %s\n", message);
	} else {
		printf("FAILURE: %s\n", message);
		pass = 0;
	}
}

int main() {
	printf("\n----CARD TEST 3: Village----\n\n");

	int numPlayers = 2;
	int kCards[10] = {smithy, adventurer, baron, feast, 
						curse, estate, duchy, province,
						silver, gold};
	int randomSeed = 50;
	struct gameState newGS;
	struct gameState oldGS;

	initializeGame(numPlayers, kCards, randomSeed, &newGS);
	memcpy(&oldGS, &newGS, sizeof(struct gameState));

	cardEffect(village, 0, 0, 0, &newGS, 0, 0);

	printf("\nTEST: 1 card drawn\n");
	myAssert(newGS.handCount[0], oldGS.handCount[0], "+1 card, -1 card");
	myAssert(newGS.numActions, oldGS.numActions + 2, "+2 actions");

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
