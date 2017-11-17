/*************************************************************
 * File: randomtestcard2.c
 * Purpose: Random test generator for the great hall dominion 
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

int main() {
	srand(time(NULL));

	printf("\n----RANDOM TEST 2: Great Hall----\n\n");

	int i;
	for (i = 0; i < MAX_TESTS; i++ ) {
		int randomSeed = rand();

		struct gameState newGS;
		struct gameState oldGS;

		int numPlayers = myRand(MIN_PLAYERS, MAX_PLAYERS);

		initializeGame(numPlayers, kCards, randomSeed, &newGS);
		memcpy(&oldGS, &newGS, sizeof(struct gameState));

		int numGreatHalls = myRand(1, 5);

		int turn = newGS.whoseTurn;

		int i;
		for (i = 0; i < numGreatHalls; i++) {
			cardEffect(great_hall, 0, 0, 0, &newGS, 0, 0);
		}
		
		printf("\nTEST: %d card(s) drawn\n", numGreatHalls);
		char handTestMsg[127];
		sprintf(handTestMsg, "+%d card(s), -%d card(s)", numGreatHalls, numGreatHalls);
		myAssert(newGS.handCount[turn], oldGS.handCount[turn], handTestMsg);

		printf("\nTEST: %d actions added\n", numGreatHalls);
		char actionTestMsg[127];
		sprintf(actionTestMsg, "+%d actions", numGreatHalls);
		myAssert(newGS.numActions, oldGS.numActions + (numGreatHalls), actionTestMsg);
	}

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
