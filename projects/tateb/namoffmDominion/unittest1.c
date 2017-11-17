/*************************************************************
 * File: unittest1.c
 * Purpose: Unit test for updateCoins() function of dominion
 * 		card game
 *************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pass = 1;
int randomSeed = 50;
int kCards[10] = {smithy, adventurer, baron, feast, 
						curse, estate, duchy, province,
						silver, gold};
int numPlayers = 3;
int maxHandCount = 5;

int c[5];
int s[5];
int g[5];

void myAssert(int actual, int expected, char* message) {
	if (actual == expected) {
		printf("SUCCESS: %s\n", message);
	} else {
		printf("FAILURE: %s\n", message);
		pass = 0;
	}
}

void startGame(struct gameState* newGS, struct gameState* oldGS) { 
	initializeGame(numPlayers, kCards, randomSeed, newGS);

	int i;
	for (i = 0; i < maxHandCount; i++) {
		c[i] = copper;
		s[i] = silver;
		g[i] = gold;
	}

	memcpy(oldGS, newGS, sizeof(struct gameState));
}

int main() {
	printf("\n----UNIT TEST 1: updateCoins()----\n\n");

	struct gameState newGS;
	struct gameState oldGS;

	int bonus;
	
	printf("\nTEST: hand full of copper\n");
	startGame(&newGS, &oldGS);
	memcpy(newGS.hand[0], c, sizeof(int) * maxHandCount);
	int i;
	for(i = 0; i < maxHandCount; i++) {
		bonus = i;
		updateCoins(0, &newGS, bonus);
		myAssert(newGS.coins, newGS.handCount[0] + bonus, "hand is full of copper");
	}

	printf("\nTEST: hand full of silver\n");
	startGame(&newGS, &oldGS);
	memcpy(newGS.hand[0], s, sizeof(int) * maxHandCount);
	for(i = 0; i < maxHandCount; i++) {
		bonus = i;
		updateCoins(0, &newGS, bonus);
		myAssert(newGS.coins, newGS.handCount[0] * 2 + bonus, "hand is full of silver");
	}

	printf("\nTEST: hand full of gold\n");
	startGame(&newGS, &oldGS);
	memcpy(newGS.hand[0], g, sizeof(int) * maxHandCount);
	for(i = 0; i < maxHandCount; i++) {
		bonus = i;
		updateCoins(0, &newGS, bonus);
		myAssert(newGS.coins, newGS.handCount[0] * 3 + bonus, "hand is full of gold");
	}

	if (pass == 1) {
		printf("\n***ALL TESTS PASSED***\n\n");
	} else {
		printf("\n***ONE OR MORE TESTS FAILED***\n\n");
	}

	return 0;
}
