/*************************************************************
 * File: randomtestadventurer.c
 * Purpose: Random test generator for the adventurer dominion 
 * 			card
 *************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_PLAYERS 2
#define MAX_TESTS 200

int pass = 1;

int kCards[10] = {smithy, adventurer, baron, feast, 
					curse, estate, duchy, province,
					silver, gold};

void myAssert(int actual, int expected, char* message) {
	if (actual == expected) {
		printf("SUCCESS: %s\n", message);
	} else {
		printf("FAILURE: %s\n", message);
		pass = 0;
	}
}

//Generate random integer from low to high, inclusive
int myRand(int low, int high) {
	int num = rand() % (high - low + 1) + low;

	return num;
}

//Fills given pile with cards and puts coppers in randomly
void treasureSpread(int cards[], int numCards, int numTreasure) {
	if (numCards > 0) {
		int i;
		for (i = 0; i < numCards; i++) {
			cards[i] = kCards[rand() % 10];
		}
		for (i = 0; i < numTreasure; i++) {
			cards[rand() % numCards] = copper;
		}
	}
}

int main() {
	srand(time(NULL));

	printf("\n----RANDOM TEST 3: Adventurer----\n\n");

	int i;
	for (i = 0; i < MAX_TESTS; i++ ) {
		int randomSeed = rand();

		struct gameState gs;

		int numPlayers = myRand(MIN_PLAYERS, MAX_PLAYERS);

		initializeGame(numPlayers, kCards, randomSeed, &gs);

		int turn = gs.whoseTurn;

		//Ensure phase == 0
		gs.phase = 0;
		//Ensure numActions > 0
		gs.numActions = (gs.numActions > 0) ? gs.numActions : 1;
		//Ensure at least one card in current player's hand
		gs.handCount[turn] = (gs.handCount[turn] > 0) ? gs.handCount[turn] : 1;
		//First card in current player's hand is adventurer
		gs.hand[turn][0] = adventurer;

		//Divide random number of cards between deck and discard
		int numCards = myRand(2, MAX_DECK);
		int divTreasure = myRand(0, 2);
		int divCards = myRand(divTreasure, numCards);
		gs.deckCount[turn] = divCards;
		gs.discardCount[turn] = numCards - divCards;
		treasureSpread(gs.deck[turn], gs.deckCount[turn], divTreasure);
		treasureSpread(gs.discard[turn], gs.discardCount[turn], 2 - divTreasure);

		int expectedCoins = gs.coins + 2;

		playCard (0, 0, 0, 0, &gs);

		printf("\nTEST: Player %d's turn\n", turn);
		myAssert(gs.whoseTurn, turn, "correct player's turn");

		printf("\nTEST: %d coins\n", expectedCoins);
		char coinTestMsg[127];
		sprintf(coinTestMsg, "expected %d coins; got %d coins", expectedCoins, gs.coins);
		myAssert(gs.coins, expectedCoins, coinTestMsg);
	}

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
