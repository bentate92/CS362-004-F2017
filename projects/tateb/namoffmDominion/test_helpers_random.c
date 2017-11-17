#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers_random.h"

void testing_header(char *s){
    printf("\nBEGIN TESTING FOR UNIT - %s\n\n", s);
}
void testing(char *s){
    printf("TESTING - %s\n", s);
}

void show_test_results(int passes, int total){
    printf("\nFAILS: %d\n", total - passes);
    printf("OVERALL: %d / %d\n\n", passes, total);
}

int assert_equal(int a, int b)
{
    if (a == b){
        return 1;
    }
    else {
        return 0;
    }
}

int assert_true(int a)
{
    if (a != 0){
        return 1;
    }
    else {
        return 0;
    }
}

void generateRandomState(struct gameState *G)
{
    int i;
    int j;
    srand(time(NULL));

    G->numPlayers = (rand() % 3) + 2;


    for (i = 0; i < G->numPlayers; i++) {

        do {
            G->deckCount[i] = rand() / (RAND_MAX / (MAX_DECK+1) + 1);
            G->handCount[i] = rand() / (RAND_MAX / (MAX_DECK+1) + 1);
            G->discardCount[i] = rand() / (RAND_MAX / (MAX_DECK+1) + 1);
            G->playedCardCount = rand() / (RAND_MAX / (MAX_DECK+1) + 1);
        }
        while ( G->deckCount[i] + G->handCount[i] + G->discardCount[i] +
                G->playedCardCount > MAX_DECK );

        for (j = 0; j < G->deckCount[i]; j++) {
            G->deck[i][j] = rand() / (RAND_MAX / (treasure_map+1) + 1);
        }
        for (j = 0; j < G->handCount[i]; j++) {
            G->hand[i][j] = rand() / (RAND_MAX / (treasure_map+1) + 1);
        }
        for (j = 0; j < G->discardCount[i]; j++) {
            G->discard[i][j] = rand() / (RAND_MAX / (treasure_map+1) + 1);
        }
        for (j = 0; j < G->playedCardCount; j++) {
            G->playedCards[j] = rand() / (RAND_MAX / (treasure_map+1) + 1);
        }
    }

    G->whoseTurn  = rand() / (RAND_MAX / G->numPlayers + 1);
    G->numActions = rand() / (RAND_MAX / 100 + 1);
    G->numBuys    = rand() / (RAND_MAX / 100 + 1);
    G->coins      = rand() / (RAND_MAX / 100 + 1);
    G->phase      = 0;

}


void printStateDetails(struct gameState G)
{
    int i, j;

    printf("Players: %d\n", G.numPlayers);
    printf("Whose Turn: %d\n", G.whoseTurn);
    printf("Played Cards: %d\n", G.playedCardCount);
    printf("Actions: %d\n", G.numActions);
    printf("Coins: %d\n", G.coins);
    printf("Buys: %d\n", G.numBuys);
    for (i = 0; i < G.numPlayers; i++){
        printf("Player %d: Hand Count: %d\n", i, G.handCount[i]);
        printf("Player %d: Deck Count: %d\n", i, G.deckCount[i]);
        printf("Player %d: Discard Count: %d\n", i, G.discardCount[i]);

        printf("Hand: ");
        for (j = 0; j < G.handCount[i]; j++){
            printf("%d ", G.hand[i][j]);
        }
        printf("\n");

        printf("Deck: ");
        for (j = 0; j < G.deckCount[i]; j++){
            printf("%d ", G.deck[i][j]);
        }
        printf("\n");

        printf("Discard: ");
        for (j = 0; j < G.discardCount[i]; j++){
            printf("%d ", G.discard[i][j]);
        }
        printf("\n");
    }
    printf("Played: ");
    for (i = 0; i < G.playedCardCount; i++){
        printf("%d ", G.playedCards[i]);
    }
    printf("\n");

}
