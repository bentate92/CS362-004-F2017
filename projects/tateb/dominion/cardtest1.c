/*************************************************************
 * File: cardtest1.c
 * Purpose: Unit test for the smithy dominion card
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
	printf("\n----CARD TEST 1: Smithy----\n\n");

	int handPos = 0;
	int bonus = 0;

	int numPlayers = 2;
	int kCards[10] = {smithy, adventurer, baron, feast, 
						curse, estate, duchy, province,
						silver, gold};
	int randomSeed = 50;
	struct gameState newGS;
	struct gameState oldGS;

	initializeGame(numPlayers, kCards, randomSeed, &newGS);

	int i;
	for (i = 0; i < 100; i++) {
		newGS.deck[0][i] = 1;
		newGS.deckCount[0]++;
	}

	memcpy(&oldGS, &newGS, sizeof(struct gameState));

	printf("\nTEST: drawing 3 cards at a time\n");
	while (newGS.deckCount[0] > 0) {
		cardEffect(smithy, 0, 0, 0, &newGS, handPos, &bonus);
		myAssert(newGS.handCount[0], oldGS.handCount[0] + 2, "3 cards drawn");
		myAssert(newGS.discardCount[0], oldGS.discardCount[0] + 1, "1 card discarded");
		memcpy(&oldGS, &newGS, sizeof(struct gameState));
	}

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}

