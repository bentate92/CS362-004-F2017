/*************************************************************
 * File: cardtest2.c
 * Purpose: Unit test for the adventurer dominion card
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

int countTreasure(struct gameState *gs) {
	int count = 0;

	int i;
	for (i = 0; i < gs->handCount[0]; i++) {
		if (gs->hand[0][i] == copper) {
			count += 1;
		}
		if (gs->hand[0][i] == silver) {
			count += 2;
		}
		if (gs->hand[0][i] == gold) {
			count += 3;
		}
	}

	return count;
}

int main() {
	printf("\n----CARD TEST 2: Adventurer----\n\n");

	int numPlayers = 2;
	int kCards[10] = {smithy, adventurer, baron, feast, 
						curse, estate, duchy, province,
						silver, gold};
	int randomSeed = 50;
	struct gameState newGS;
	struct gameState oldGS;

	int i;
	for (i = 0; i < 5; i++) {
		initializeGame(numPlayers, kCards, randomSeed, &newGS);
	
		int j;
		for (j = 0; j < 5; j++) {
			newGS.deck[0][j] = smithy;
			newGS.hand[0][j] = minion;
		} 

		printf("\nTEST: %d treasure in deck\n", i);

		for (j = 0; j < i; j++) {
			newGS.deck[0][j+2] = gold;
		}
	
		memcpy(&oldGS, &newGS, sizeof(struct gameState));


		cardEffect(adventurer, 0, 0, 0, &newGS, 0, 0);


		if (i == 0) {
			myAssert(newGS.handCount[0], oldGS.handCount[0], "no treasure in deck");
			myAssert(countTreasure(&newGS), countTreasure(&oldGS), "no new treasure in hand");
		} else if (i == 1) {
			myAssert(newGS.deckCount[0], oldGS.deckCount[0] - 5, "5 cards drawn from deck");
			myAssert(newGS.handCount[0], oldGS.handCount[0] + 1, "1 card added to hand");
			myAssert(newGS.discardCount[0], oldGS.discardCount[0] + 4, "4 cards added to discard");
			myAssert(countTreasure(&newGS), countTreasure(&oldGS) + 3, "got 3 treasure");
		} else {
			myAssert(newGS.deckCount[0], oldGS.deckCount[0] - 4, "4 cards drawn from deck");
			myAssert(newGS.handCount[0], oldGS.handCount[0] + 2, "2 cards added to hand");
			myAssert(newGS.discardCount[0], oldGS.discardCount[0] + 2, "2 cards added to discard");
			myAssert(countTreasure(&newGS), countTreasure(&oldGS) + 6, "got 6 treasure");
		}
	}

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
