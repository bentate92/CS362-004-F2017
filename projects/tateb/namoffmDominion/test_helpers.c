#include <stdio.h>
#include "test_helpers.h"

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

int assert_equal(int a, int b){
    if (a == b){
        printf("\tPASS!\n");
        return 1;
    }
    else {
        printf("\t\tFAIL!\n");
        return 0;
    }
}

int assert_true(int a){
    if (a != 0){
        printf("\tPASS!\n");
        return 1;
    }
    else {
        printf("\t\tFAIL!\n");
        return 0;
    }
}
