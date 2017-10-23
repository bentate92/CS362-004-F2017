/*************************************************************
 * File: unittest2.c
 * Purpose: Unit test for drawCard() function of dominion
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

void testHandCountUp(struct gameState* newGS, struct gameState* oldGS) {
	int res = newGS->handCount[0] - oldGS->handCount[0];
	myAssert(res, 1, "1 card added to hand");
}

void testDrawAll(struct gameState* newGS, struct gameState* oldGS, int currPlayer) {
	int i = 1;
	while (newGS->deckCount[currPlayer] > 0) {
		printf("Drawing card #%d...\n", i);

		int res = drawCard(currPlayer, newGS);
		testHandCountUp(newGS, oldGS);

		int deckDown = oldGS->deckCount[0] - newGS->deckCount[0];
		myAssert(deckDown, 1, "1 card removed from deck");

		int drawnCardInHand = newGS->hand[0][newGS->handCount[0] - 1];
		int drawnCardFromDeck = oldGS->deck[0][oldGS->deckCount[0]-1];
		myAssert(drawnCardInHand, drawnCardFromDeck, "newest card in hand matches card drawn from deck");

		myAssert(res, 0, "card successfully drawn");
		memcpy(oldGS, newGS, sizeof(struct gameState));
		
		i++;
	}
}

int main() {
	printf("\n----UNIT TEST 2: drawCard()----\n\n");

	int numPlayers = 2;
	int kingdomCards[10] = {smithy, adventurer, baron, feast, 
							curse, estate, duchy, province,
							silver, gold};
	int randomSeed = 42;
	struct gameState newGS;
	struct gameState oldGS;

	initializeGame(numPlayers, kingdomCards, randomSeed, &newGS);
	memcpy(&oldGS, &newGS, sizeof(struct gameState));

	int currPlayer = newGS.whoseTurn;

	printf("\nTEST: Drawing all cards from deck....\n");
	testDrawAll(&newGS, &oldGS, currPlayer);

	printf("\nTEST: Drawing when deck and discard are empty....\n");
	int bothEmpty = drawCard(0, &newGS);
	myAssert(newGS.deckCount[0], 0, "deck is empty");
	myAssert(newGS.discardCount[0], 0, "discard is empty");
	myAssert(newGS.handCount[0] - oldGS.handCount[0], 0, "handcount remains the same");
	myAssert(bothEmpty, -1, "returns -1 when deck and discard are empty");
	memcpy(&oldGS, &newGS, sizeof(struct gameState));

	//Discard entire hand to prepare for next test
	int position = newGS.handCount[currPlayer] - 1;
	int i;
	for (i = 0; i < 10; i++) {
		newGS.discard[currPlayer][i] = newGS.hand[currPlayer][i];
		newGS.hand[currPlayer][i] = -1;
		newGS.handCount[currPlayer]--;
		newGS.discardCount[currPlayer]++;
		position--;
		memcpy(&oldGS, &newGS, sizeof(struct gameState));
	}
	
	printf("\nTEST: Drawing when deck is empty and discard isn't....\n");
	int emptyDeck = drawCard(0, &newGS);
	myAssert(newGS.deckCount[0], oldGS.discardCount[0] - 1, "deck contains 1 less card than discard did");
	testHandCountUp(&newGS, &oldGS);
	myAssert(emptyDeck, 0, "card successfully drawn from discard");
	memcpy(&oldGS, &newGS, sizeof(struct gameState));

	printf("\nTEST: Drawing all cards from deck....\n");
	testDrawAll(&newGS, &oldGS, currPlayer);

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
