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
int baron_funct(struct gameState* state, int currentPlayer, int handPos, int choice1) {
    //Increase buys by 1!
    state->numBuys++;
    //Boolean true or going to discard an estate
    if (choice1 > 0) {
        int i;
        //Search for estate card
        for(i; i < state->handCount[currentPlayer]; i++) {
            //Found an estate card!
            if (state->hand[currentPlayer][i] == estate) {
                //Add 4 coins to the amount of coins
                state->coins += 4;
                //Discard estate card
                discardCard(i, currentPlayer, state, 0);
                return 0;
            }
        }
        if(DEBUG) {
            printf("No estate cards in your hand, invalid choice\n");
            printf("Must gain an estate if there are any\n");
        }
        //Gain an estate if couldn't discard
        gainCard(estate, state, 0, currentPlayer);
    }

    else {
        //Gain an estate
        gainCard(estate, state, 0, currentPlayer);
    }

    return 0;
}

int main() {
    printf("\n*************************************************************\nbaron_funct\n*************************************************************\n\n");
    //Variables
    int result;
    int assertResult;

    //Variable intilization
    printf("UNIT TEST: Choose to gain estate\n");
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->coins = 0;
    state->numBuys = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = baron;
    state->hand[0][1] = estate;     //In case it decides to take this anyway
    state->discardCount[0] = 0;
    state->playedCardCount = 0;

    //Function call (Chooses to gain estate)
    result = baron_funct(state, 0, 0, 0);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No coins gained", 0, state->coins);
    assertResult = assert("Buys incremented correctly", 1, state->numBuys);
    assertResult = assert("Baron card removed", 1, state->handCount[0]);
    assertResult = assert("Estate card remained", estate, state->hand[0][0]);
    assertResult = assert("No other card", -1, state->hand[0][1]);
    assertResult = assert("Card gained", 1, state->discardCount[0]);
    assertResult = assert("Estate Card gained", estate, state->discard[0][0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Baron Card played", baron, state->playedCards[0]);


    //Variable intilization
    printf("\nUNIT TEST: Choose to discard estate\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->coins = 0;
    state->numBuys = 0;
    state->handCount[0] = 2;
    state->hand[0][0] = baron;
    state->hand[0][1] = estate;
    state->discardCount[0] = 0;
    state->playedCardCount = 0;

    //Function call (Chooses to discard estate)
    result = baron_funct(state, 0, 0, 1);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Coins gained", 4, state->coins);
    assertResult = assert("Buys incremented correctly", 1, state->numBuys);
    assertResult = assert("Baron and Estate card removed", 0, state->handCount[0]);
    assertResult = assert("Cards played", 2, state->playedCardCount);
    assertResult = assert("Baron Card played", baron, state->playedCards[0]);
    assertResult = assert("Estate Card discarded", estate, state->playedCards[1]);


    //Variable intilization
    printf("\nUNIT TEST: Choose to discard estate, but can't\n");
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->coins = 0;
    state->numBuys = 0;
    state->handCount[0] = 1;
    state->hand[0][0] = baron;
    state->discardCount[0] = 0;
    state->playedCardCount = 0;

    //Function call (Chooses to discard estate, but can't)
    result = baron_funct(state, 0, 0, 1);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("No coins gained", 0, state->coins);
    assertResult = assert("Buys incremented correctly", 1, state->numBuys);
    assertResult = assert("Baron card removed", 1, state->handCount[0]);
    assertResult = assert("No other card", -1, state->hand[0][1]);
    assertResult = assert("Card gained", 1, state->discardCount[0]);
    assertResult = assert("Estate Card gained", estate, state->discard[0][0]);
    assertResult = assert("Card played", 1, state->playedCardCount);
    assertResult = assert("Baron Card played", baron, state->playedCards[0]);

    assertResult = assertResult + 1;
    printf("\n");
    free(state);
    return 0;
}
