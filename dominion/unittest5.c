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
int mine_funct(struct gameState* state, int currentPlayer, int handPos, int choice1, int choice2) {

    //int j = state->hand[currentPlayer][choice1];  //store card we will trash

    if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
    {
        return -1;
    }

    if (choice2 > gold || choice2 < copper)
    {
        return -1;
    }

    if ( (getCost(state->hand[currentPlayer][choice1]) + 3) < getCost(choice2) )
    {
        return -1;
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    //discard trashed card
    discardCard(state->hand[currentPlayer][choice1], currentPlayer, state, 1);
    //gain chosen card
    gainCard(choice2, state, 0, currentPlayer);

    return 0;
}

int main() {
    //Variables
    int result;
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
    result = mine_funct(state, 0, 0, 1, copper);

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
    result = mine_funct(state, 0, 0, 1, estate);

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
    result = mine_funct(state, 0, 0, 1, gold);

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
    result = mine_funct(state, 0, 0, 1, silver);

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
    result = mine_funct(state, 0, 0, 2, silver);

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
