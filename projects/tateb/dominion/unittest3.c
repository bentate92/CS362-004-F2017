/*************************************************************
 * File: unittest3.c
 * Purpose: Unit test for isGameOver() function of dominion
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
	printf("\n----UNIT TEST 3: isGameOver()----\n\n");

	int numPlayers = 2;
	int randomSeed = 50;
	int kCards[10] = {smithy, adventurer, baron, feast, 
						curse, estate, duchy, province,
						silver, gold};
	struct gameState gs;

	initializeGame(numPlayers, kCards, randomSeed, &gs);

	printf("\nTEST: empty province supply pile\n");
	gs.supplyCount[province] = 0;
	myAssert(isGameOver(&gs), 1, "game ends when province supply pile empty");


	printf("\nTEST: 3 empty supply piles\n");
	int i;
	for (i = 0; i < 3; i++) {
		initializeGame(numPlayers, kCards, randomSeed, &gs);

		int j;
		for (j = 0; j < 10; j++) {
			gs.supplyCount[kCards[j]] = 0;
			
			int count = 0;

			int k;
			for (k = 0; k < 10; k++) {
				if (gs.supplyCount[kCards[k]] == 0) {
					count++;
				}
			}

			if (count < 3) {
				myAssert(isGameOver(&gs), 0, "game not over (less than 3 empty piles)");
			} else {
				myAssert(isGameOver(&gs), 1, "game over (at least 3 empty piles)");
			}
		}
	}

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
