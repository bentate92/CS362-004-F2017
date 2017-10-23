/*************************************************************
 * File: unittest4.c
 * Purpose: Unit test for fullDeckCount() function of dominion
 * 		card game
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
	printf("\n----UNIT TEST 4: fullDeckCount()----\n\n");

	int numPlayers = 2;
	int kCards[10] = {smithy, adventurer, baron, feast, 
						curse, estate, duchy, province,
						silver, gold};
	int randomSeed = 50;
	struct gameState gs;

	initializeGame(numPlayers, kCards, randomSeed, &gs);

	printf("\ndeck = %d", gs.deckCount[0]);
	printf("\nhand = %d", gs.handCount[0]);

	printf("\nTEST: no smithys, discard empty, deck and hand have 5\n");
	myAssert(fullDeckCount(0, smithy, &gs), 0, "no smithys");
	myAssert(gs.discardCount[0], 0, "discard empty");
	myAssert(gs.deckCount[0], 5, "deck has 5 cards");
	myAssert(gs.handCount[0], 5, "hand has 5 cards");

	printf("\nTEST: one smithy added to discard\n");
	gainCard(smithy, &gs, 0, 0);
	myAssert(fullDeckCount(0, smithy, &gs), 1, "1 smithy");
	myAssert(gs.discardCount[0], 1, "discard has 1 card");
	myAssert(gs.deckCount[0], 5, "deck has 5 cards");
	myAssert(gs.handCount[0], 5, "hand has 5 cards");

	printf("\nTEST: one smithy added to deck\n");
	gainCard(smithy, &gs, 1, 0);
	myAssert(fullDeckCount(0, smithy, &gs), 2, "2 smithys");
	myAssert(gs.discardCount[0], 1, "discard has 1 card");
	myAssert(gs.deckCount[0], 6, "deck has 6 cards");
	myAssert(gs.handCount[0], 5, "hand has 5 cards");

	printf("\nTEST: one smithy added to hand\n");
	gainCard(smithy, &gs, 2, 0);
	myAssert(fullDeckCount(0, smithy, &gs), 3, "3 smithys");
	myAssert(gs.discardCount[0], 1, "discard has 1 card");
	myAssert(gs.deckCount[0], 6, "deck has 6 cards");
	myAssert(gs.handCount[0], 6, "hand has 6 cards");

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
