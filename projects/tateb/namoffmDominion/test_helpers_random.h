#ifndef TEST_HELPERS_RANDOM_H
#define TEST_HELPERS_RANDOM_H

#include "dominion.h"

void testing_header(char *s);
void testing(char *s);
void show_test_results(int passes, int total);
int  assert_equal(int a, int b);
int  assert_true(int a);
void generateRandomState(struct gameState *G);
void printStateDetails(struct gameState G);

#endif
