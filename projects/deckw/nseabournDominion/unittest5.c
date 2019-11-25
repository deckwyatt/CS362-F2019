#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

int assert(char* test, int target, int variable) {
    if (target != variable) {
        printf("TEST FAILED: '%s', Wanted: %d, GOT: %d\n", test, target, variable);
        return 0;
    }
    else {
        printf("SUCCESS\n");
        return 1;
    }
}

int main() {
    //Variables
    int result;
    int blank;
    int assertResult;
    int i;

    //Variable intilization
    printf("UNIT TEST: Choice1 not treasure\n");
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = mine;
    state->hand[0][1] = mine;
    state->playedCardCount = 0;

    //Function call (Choice1 not treasure)
    result = cardEffect(mine, 1, copper, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited with error", -1, result);
    assertResult = assert("Hand unchanged", 2, state->handCount[0]);
    assertResult = assert("First Mine card remained", mine, state->hand[0][0]);
    assertResult = assert("Second Mine card remained", mine, state->hand[0][1]);

    //Variable intilization
    printf("\nUNIT TEST: Choice2 not treasure\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = mine;
    state->hand[0][1] = copper;
    state->playedCardCount = 0;

    //Function call (Choice2 not treasure)
    result = cardEffect(mine, 1, estate, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited with error", -1, result);
    assertResult = assert("Hand unchanged", 2, state->handCount[0]);
    assertResult = assert("Mine card remained", mine, state->hand[0][0]);
    assertResult = assert("Copper card remained", copper, state->hand[0][1]);

    //Variable intilization
    printf("\nUNIT TEST: Invalid Selection\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = mine;
    state->hand[0][1] = copper;
    state->playedCardCount = 0;

    //Function call (Invalid Selection)
    result = cardEffect(mine, 1, gold, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited with error", -1, result);
    assertResult = assert("Hand unchanged", 2, state->handCount[0]);
    assertResult = assert("Mine card remained", mine, state->hand[0][0]);
    assertResult = assert("Copper card remained", copper, state->hand[0][1]);

    //Variable intilization
    printf("\nUNIT TEST: Valid Selection\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = mine;
    state->hand[0][1] = copper;
    state->playedCardCount = 0;

    //Function call (Valid Selection)
    result = cardEffect(mine, 1, silver, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Mine removed", 1, state->handCount[0]);
    assertResult = assert("Card is a Silver", silver, state->hand[0][0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Mine card played", mine, state->playedCards[0]);

    //Variable intilization
    printf("\nUNIT TEST: Valid Selection with full hand\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = mine;
    state->hand[0][1] = estate;
    state->hand[0][2] = copper;
    state->hand[0][3] = estate;
    state->hand[0][4] = estate;
    state->playedCardCount = 0;

    //Function call (Valid Selection)
    result = cardEffect(mine, 2, silver, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Mine removed", 4, state->handCount[0]);
    assertResult = assert("Card is an Estate", estate, state->hand[0][0]);
    assertResult = assert("Card is an Estate", estate, state->hand[0][1]);
    assertResult = assert("Card is an Estate", estate, state->hand[0][2]);
    assertResult = assert("Card is a Silver", silver, state->hand[0][3]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Mine card played", mine, state->playedCards[0]);

    free(state);
    return 0;
}
