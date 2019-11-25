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
        printf("SUCCESS: %s\n", test);
        return 1;
    }
}

int main() {
    printf("\n*************************************************************\nambassador_funct\n*************************************************************\n\n");
    //Variables
    int result;
    int blank;
    int assertResult;

    //Variable intilization
    printf("UNIT TEST: Choose to remove less than 0 cards\n");
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 3;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->hand[0][2] = estate;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 0;

    //Function call (Chooses to remove less than 0 cards)
    result = cardEffect(ambassador, 1, -1, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited with an error", -1, result);
    assertResult = assert("No card removed", 3, state->handCount[0]);
    assertResult = assert("Ambassador card remained", ambassador, state->hand[0][0]);
    assertResult = assert("First Estate card remained", estate, state->hand[0][1]);
    assertResult = assert("Second Estate card remained", estate, state->hand[0][2]);
    assertResult = assert("No cards played", 0, state->playedCardCount);
    assertResult = assert("Other player didn't gain cards", 0, state->discardCount[1]);
    assertResult = assert("Supply not increased", 0, state->supplyCount[estate]);


    //Variable intilization
    printf("\nUNIT TEST: Choose to remove more than 2 cards\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 4;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->hand[0][2] = estate;
    state->hand[0][3] = estate;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 0;

    //Function call (Chooses to remove more than 2 cards)
    result = cardEffect(ambassador, 1, 3, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited with an error", -1, result);
    assertResult = assert("No card removed", 4, state->handCount[0]);
    assertResult = assert("Ambassador card remained", ambassador, state->hand[0][0]);
    assertResult = assert("First Estate card remained", estate, state->hand[0][1]);
    assertResult = assert("Second Estate card remained", estate, state->hand[0][2]);
    assertResult = assert("Third Estate card remained", estate, state->hand[0][3]);
    assertResult = assert("No cards played", 0, state->playedCardCount);
    assertResult = assert("Other player didn't gain cards", 0, state->discardCount[1]);
    assertResult = assert("Supply not increased", 0, state->supplyCount[estate]);


    //Variable intilization
    printf("\nUNIT TEST: Choose to reveal played card\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 4;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->hand[0][2] = estate;
    state->hand[0][3] = estate;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 0;

    //Function call (Chooses to reveal played card)
    result = cardEffect(ambassador, 0, 1, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited with an error", -1, result);
    assertResult = assert("No card removed", 4, state->handCount[0]);
    assertResult = assert("Ambassador card remained", ambassador, state->hand[0][0]);
    assertResult = assert("First Estate card remained", estate, state->hand[0][1]);
    assertResult = assert("Second Estate card remained", estate, state->hand[0][2]);
    assertResult = assert("Third Estate card remained", estate, state->hand[0][3]);
    assertResult = assert("No cards played", 0, state->playedCardCount);
    assertResult = assert("Other player didn't gain cards", 0, state->discardCount[1]);
    assertResult = assert("Supply not increased", 0, state->supplyCount[estate]);


    //Variable intilization
    printf("\nUNIT TEST: Choose to return too many cards\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 0;

    //Function call (Chooses to return too many cards)
    result = cardEffect(ambassador, 1, 2, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited with an error", -1, result);
    assertResult = assert("No card removed", 2, state->handCount[0]);
    assertResult = assert("Ambassador card remained", ambassador, state->hand[0][0]);
    assertResult = assert("First Estate card remained", estate, state->hand[0][1]);
    assertResult = assert("No cards played", 0, state->playedCardCount);
    assertResult = assert("Other player didn't gain cards", 0, state->discardCount[1]);
    assertResult = assert("Supply not increased", 0, state->supplyCount[estate]);


    //Variable intilization
    printf("\nUNIT TEST: Valid play (remove 0 cards)\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 4;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->hand[0][2] = estate;
    state->hand[0][3] = estate;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 1;

    //Function call (Valid play)
    result = cardEffect(ambassador, 1, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Correct number of cards removed", 3, state->handCount[0]);
    assertResult = assert("First card is an estate", estate, state->hand[0][0]);
    assertResult = assert("Second card is an estate", estate, state->hand[0][1]);
    assertResult = assert("Third card is an estate", estate, state->hand[0][2]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Ambassador card played", ambassador, state->playedCards[0]);
    assertResult = assert("Other player gains 1 card", 1, state->discardCount[1]);
    assertResult = assert("Other player gains 1 estate card", 1, state->discard[1][0]);
    assertResult = assert("Supply nets -1", 0, state->supplyCount[estate]);


    //Variable intilization
    printf("\nUNIT TEST: Valid play (remove 1 card)\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 4;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->hand[0][2] = estate;
    state->hand[0][3] = estate;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 1;

    //Function call (Valid play)
    result = cardEffect(ambassador, 1, 1, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Correct number of cards removed", 2, state->handCount[0]);
    assertResult = assert("First card is an estate", estate, state->hand[0][0]);
    assertResult = assert("Second card is an estate", estate, state->hand[0][1]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Ambassador card played", ambassador, state->playedCards[0]);
    assertResult = assert("Other player gains 1 card", 1, state->discardCount[1]);
    assertResult = assert("Other player gains 1 estate card", 1, state->discard[1][0]);
    assertResult = assert("Supply nets no cards", 1, state->supplyCount[estate]);


    //Variable intilization
    printf("\nUNIT TEST: Valid play (remove 2 cards)\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 4;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->hand[0][2] = estate;
    state->hand[0][3] = estate;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 1;

    //Function call (Valid play)
    result = cardEffect(ambassador, 1, 2, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Correct number of cards removed", 1, state->handCount[0]);
    assertResult = assert("First card is an estate", estate, state->hand[0][0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Ambassador card played", ambassador, state->playedCards[0]);
    assertResult = assert("Other player gains 1 card", 1, state->discardCount[1]);
    assertResult = assert("Other player gains 1 estate card", 1, state->discard[1][0]);
    assertResult = assert("Supply nets 1", 2, state->supplyCount[estate]);


    //Variable intilization
    printf("\nUNIT TEST: Valid play (remove 2 cards, other cards in hand)\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = ambassador;
    state->hand[0][1] = estate;
    state->hand[0][2] = ambassador;
    state->hand[0][3] = estate;
    state->hand[0][4] = ambassador;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->supplyCount[estate] = 1;

    //Function call (Valid play)
    result = cardEffect(ambassador, 1, 2, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Correct number of cards removed", 2, state->handCount[0]);
    assertResult = assert("First card is an ambassador", ambassador, state->hand[0][0]);
    assertResult = assert("Second card is an ambassador", ambassador, state->hand[0][1]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Ambassador card played", ambassador, state->playedCards[0]);
    assertResult = assert("Other player gains 1 card", 1, state->discardCount[1]);
    assertResult = assert("Other player gains 1 estate card", 1, state->discard[1][0]);
    assertResult = assert("Supply nets 1", 2, state->supplyCount[estate]);


    assertResult = assertResult + 1;
    printf("\n");
    free(state);
    return 0;
}
