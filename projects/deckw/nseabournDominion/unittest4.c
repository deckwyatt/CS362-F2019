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
    printf("\n*************************************************************\ntribute_funct\n*************************************************************\n\n");
    //Variables
    int i;
    int result;
    int blank;
    int assertResult;
    int tributeRevealedCards[2] = {-1, -1};

    //Variable intilization
    printf("UNIT TEST: Opponent has 2 victory cards\n");
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 2;
    state->deck[1][0] = estate;
    state->deck[1][1] = gardens;

    //Function call (Opponent has 2 victory cards)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No Actions gained", 0, state->numActions);
    assertResult = assert("No coins gained", 0, state->coins);
    assertResult = assert("4 cards drawn", 4, state->handCount[0]);
    assertResult = assert("First card is an Estate", estate, state->hand[0][0]);
    assertResult = assert("Second card is an Estate", estate, state->hand[0][1]);
    assertResult = assert("Third card is an Estate", estate, state->hand[0][2]);
    assertResult = assert("Fourth card is an Estate", estate, state->hand[0][3]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player put cards into discard pile", 2, state->discardCount[1]);
    assertResult = assert("First card in discard pile is gardens", gardens, state->discard[1][0]);
    assertResult = assert("Second card in discard pile is estate", estate, state->discard[1][1]);
    assertResult = assert("Other player removed cards from deck", 0, state->deckCount[1]);


    //Variable intilization
    printf("\nUNIT TEST: Opponent has 2 of the same victory card\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 2;
    state->deck[1][0] = estate;
    state->deck[1][1] = estate;

    //Function call (Opponent has 2 of the same victory cards)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No Actions gained", 0, state->numActions);
    assertResult = assert("No coins gained", 0, state->coins);
    assertResult = assert("2 cards drawn", 2, state->handCount[0]);
    assertResult = assert("First card is an Estate", estate, state->hand[0][0]);
    assertResult = assert("Second card is an Estate", estate, state->hand[0][1]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player put cards into discard pile", 2, state->discardCount[1]);
    assertResult = assert("First card in discard pile is estate", estate, state->discard[1][0]);
    assertResult = assert("Second card in discard pile is estate", estate, state->discard[1][1]);
    assertResult = assert("Other player removed cards from deck", 0, state->deckCount[1]);


    //Variable intilization
    printf("\nUNIT TEST: Opponent has 2 treasure cards\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 2;
    state->deck[1][0] = copper;
    state->deck[1][1] = gold;

    //Function call (Opponent has 2 treasure cards)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No Actions gained", 0, state->numActions);
    assertResult = assert("4 coins gained", 4, state->coins);
    assertResult = assert("No cards drawn", 0, state->handCount[0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player put cards into discard pile", 2, state->discardCount[1]);
    assertResult = assert("First card in discard pile is gold", gold, state->discard[1][0]);
    assertResult = assert("Second card in discard pile is copper", copper, state->discard[1][1]);
    assertResult = assert("Other player removed cards from deck", 0, state->deckCount[1]);

    //Variable intilization
    printf("\nUNIT TEST: Opponent has 2 of the same treasure card\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 2;
    state->deck[1][0] = copper;
    state->deck[1][1] = copper;

    //Function call (Opponent has 2 of the same treasure cards)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No Actions gained", 0, state->numActions);
    assertResult = assert("2 coins gained", 2, state->coins);
    assertResult = assert("No cards drawn", 0, state->handCount[0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player put cards into discard pile", 2, state->discardCount[1]);
    assertResult = assert("First card in discard pile is copper", copper, state->discard[1][0]);
    assertResult = assert("Second card in discard pile is copper", copper, state->discard[1][1]);
    assertResult = assert("Other player removed cards from deck", 0, state->deckCount[1]);


    //Variable intilization
    printf("\nUNIT TEST: Opponent has 2 action cards\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 2;
    state->deck[1][0] = tribute;
    state->deck[1][1] = ambassador;

    //Function call (Opponent has 2 action cards)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("4 Actions gained", 4, state->numActions);
    assertResult = assert("No coins gained", 0, state->coins);
    assertResult = assert("No cards drawn", 0, state->handCount[0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player put cards into discard pile", 2, state->discardCount[1]);
    assertResult = assert("First card in discard pile is ambassador", ambassador, state->discard[1][0]);
    assertResult = assert("Second card in discard pile is tribute", tribute, state->discard[1][1]);
    assertResult = assert("Other player removed cards from deck", 0, state->deckCount[1]);


    //Variable intilization
    printf("\nUNIT TEST: Opponent has 2 of the same action card\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 2;
    state->deck[1][0] = tribute;
    state->deck[1][1] = tribute;

    //Function call (Opponent has 2 action cards)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("2 Actions gained", 2, state->numActions);
    assertResult = assert("No coins gained", 0, state->coins);
    assertResult = assert("No cards drawn", 0, state->handCount[0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player put cards into discard pile", 2, state->discardCount[1]);
    assertResult = assert("First card in discard pile is tribute", tribute, state->discard[1][0]);
    assertResult = assert("Second card in discard pile is tribute", tribute, state->discard[1][1]);
    assertResult = assert("Other player removed cards from deck", 0, state->deckCount[1]);


    //Variable intilization
    printf("\nUNIT TEST: Opponent has no cards in deck\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 2;
    state->discard[1][0] = copper;
    state->discard[1][1] = copper;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 0;

    //Function call (Opponent has no cards in deck)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No Actions gained", 0, state->numActions);
    assertResult = assert("2 coins gained", 2, state->coins);
    assertResult = assert("No cards drawn", 0, state->handCount[0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player put cards into discard pile", 2, state->discardCount[1]);
    assertResult = assert("First card in discard pile is copper", copper, state->discard[1][0]);
    assertResult = assert("Second card in discard pile is copper", copper, state->discard[1][1]);
    assertResult = assert("Other player removed cards from deck", 0, state->deckCount[1]);


    //Variable intilization
    printf("\nUNIT TEST: Opponent has no cards\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = tribute;
    state->playedCardCount = 0;
    state->discardCount[1] = 0;
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->deckCount[1] = 0;
    for(i = 0; i < state->discardCount[1]; i++){
        state->discard[1][i] = -1;
    }

    //Function call (Opponent has no cards)
    result = cardEffect(tribute, 0, 0, 0, state, 0, &blank);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No actions gained", 0, state->numActions);
    assertResult = assert("No coins gained", 0, state->coins);
    assertResult = assert("No cards drawn", 0, state->handCount[0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Tribute card played", tribute, state->playedCards[0]);
    assertResult = assert("Other player has no cards in discard pile", 0, state->discardCount[1]);
    assertResult = assert("Other player has no cards in deck", 0, state->deckCount[1]);


    assertResult = assertResult + 1;
    printf("\n");
    free(state);
    return 0;
}
