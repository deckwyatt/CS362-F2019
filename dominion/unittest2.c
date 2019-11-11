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
int minion_funct(struct gameState* state, int currentPlayer, int handPos, int choice1, int choice2) {
    int i;
    int j;

    //remove minion from hands
    discardCard(handPos, currentPlayer, state, 0);
    //+1 action
    state->numActions++;

    if (choice1)
    {
        state->coins = state->coins + 2;
    }
    else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    {
        //discard hand
        while(numHandCards(state) > 0)
        {
            discardCard(0, currentPlayer, state, 0);
        }
        //draw 4
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, state);
        }

        //other players discard hand and redraw if hand size > 4
        for (i = 0; i < state->numPlayers; i++)
        {
            //have 5 or more cards only
            if (i == currentPlayer || state->handCount[i] > 5)
            {
                //discard hand
                while( state->handCount[i] > 0 )
                {
                    //discard first card
                    discardCard(0, i, state, 0);
                }
                //draw 4
                for (j = 0; j < 4; j++)
                {
                    drawCard(i, state);
                }
            }
        }

    }
    return 0;
}

int main() {
    printf("\n*************************************************************\nminion_funct\n*************************************************************\n\n");
    //Variables
    int result;
    int assertResult;
    int i;

    //Variable intilization
    printf("UNIT TEST: Choose to gain coins\n");
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->handCount[0] = 3;
    state->hand[0][0] = minion;
    state->hand[0][1] = estate;
    state->hand[0][2] = estate;
    state->playedCardCount = 0;

    //Function call (Chooses to gain coins)
    result = minion_funct(state, 0, 0, 1, 0);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Action gained", 1, state->numActions);
    assertResult = assert("2 coins gained", 2, state->coins);
    assertResult = assert("Minion card removed", 2, state->handCount[0]);
    assertResult = assert("First Estate card remained", estate, state->hand[0][0]);
    assertResult = assert("Second Estate card remained", estate, state->hand[0][1]);
    assertResult = assert("Cards added to discard", 1, state->playedCardCount);
    assertResult = assert("Minion Card added to discard", minion, state->playedCards[0]);


    //Variable intilization
    printf("\nUNIT TEST: Choose to wheel hand\n");
    state->numPlayers = 7;
    state->whoseTurn = 0;
    state->numActions = 0;
    state->coins = 0;
    state->playedCardCount = 0;

    //1st player
    state->handCount[0] = 5;
    state->hand[0][0] = minion;
    for(i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = estate;
    }
    state->deckCount[0] = 60;
    for(i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = estate;
    }
    state->discardCount[0] = 0;

    //2nd player
    state->handCount[1] = 1;
    for(i = 0; i < state->handCount[1]; i++){
        state->hand[1][i] = estate;
    }
    state->deckCount[1] = 60;
    for(i = 0; i < state->deckCount[1]; i++){
        state->deck[1][i] = estate;
    }
    state->discardCount[1] = 0;

    //3rd player
    state->handCount[2] = 2;
    for(i = 0; i < state->handCount[2]; i++){
        state->hand[2][i] = estate;
    }
    state->deckCount[2] = 60;
    for(i = 0; i < state->deckCount[2]; i++){
        state->deck[2][i] = estate;
    }
    state->discardCount[2] = 0;

    //4th player
    state->handCount[3] = 3;
    for(i = 0; i < state->handCount[3]; i++){
        state->hand[3][i] = estate;
    }
    state->deckCount[3] = 60;
    for(i = 0; i < state->deckCount[3]; i++){
        state->deck[3][i] = estate;
    }
    state->discardCount[3] = 0;

    //5th player
    state->handCount[4] = 4;
    for(i = 0; i < state->handCount[4]; i++){
        state->hand[4][i] = estate;
    }
    state->deckCount[4] = 60;
    for(i = 0; i < state->deckCount[4]; i++){
        state->deck[4][i] = estate;
    }
    state->discardCount[4] = 0;

    //6th player
    state->handCount[5] = 5;
    for(i = 0; i < state->handCount[5]; i++){
        state->hand[5][i] = estate;
    }
    state->deckCount[5] = 60;
    for(i = 0; i < state->deckCount[5]; i++){
        state->deck[5][i] = estate;
    }
    state->discardCount[5] = 0;

    //7th player
    state->handCount[6] = 6;
    for(i = 0; i < state->handCount[6]; i++){
        state->hand[6][i] = estate;
    }
    state->deckCount[6] = 60;
    for(i = 0; i < state->deckCount[6]; i++){
        state->deck[6][i] = estate;
    }
    state->discardCount[6] = 0;

    //Function call (Chooses to gain coins)
    result = minion_funct(state, 0, 0, 0, 1);

    //Assertions
    assertResult = assert("Function exited correctly", 0, result);
    assertResult = assert("Action gained", 1, state->numActions);
    assertResult = assert("No coins gained", 0, state->coins);

    assertResult = assert("1st Redrew", 4, state->handCount[0]);
    assertResult = assert("1st: 1st Card Estate", estate, state->hand[0][0]);
    assertResult = assert("1st: 2nd Card Estate", estate, state->hand[0][1]);
    assertResult = assert("1st: 3rd Card Estate", estate, state->hand[0][2]);
    assertResult = assert("1st: 4th Card Estate", estate, state->hand[0][3]);

    assertResult = assert("2nd Didn't Redrew", 1, state->handCount[1]);
    assertResult = assert("2nd: 1st Card Estate", estate, state->hand[1][0]);

    assertResult = assert("3rd Didn't Redrew", 2, state->handCount[2]);
    assertResult = assert("3rd: 1st Card Estate", estate, state->hand[2][0]);
    assertResult = assert("3rd: 2nd Card Estate", estate, state->hand[2][1]);

    assertResult = assert("4th Didn't Redrew", 3, state->handCount[3]);
    assertResult = assert("4th: 1st Card Estate", estate, state->hand[3][0]);
    assertResult = assert("4th: 2nd Card Estate", estate, state->hand[3][1]);
    assertResult = assert("4th: 3rd Card Estate", estate, state->hand[3][2]);

    assertResult = assert("5th Didn't Redrew", 4, state->handCount[4]);
    assertResult = assert("5th: 1st Card Estate", estate, state->hand[4][0]);
    assertResult = assert("5th: 2nd Card Estate", estate, state->hand[4][1]);
    assertResult = assert("5th: 3rd Card Estate", estate, state->hand[4][2]);
    assertResult = assert("5th: 4th Card Estate", estate, state->hand[4][3]);

    assertResult = assert("6th Redrew", 4, state->handCount[5]);
    assertResult = assert("6th: 1st Card Estate", estate, state->hand[5][0]);
    assertResult = assert("6th: 2nd Card Estate", estate, state->hand[5][1]);
    assertResult = assert("6th: 3rd Card Estate", estate, state->hand[5][2]);
    assertResult = assert("6th: 4th Card Estate", estate, state->hand[5][3]);

    assertResult = assert("7th Redrew", 4, state->handCount[6]);
    assertResult = assert("7th: 1st Card Estate", estate, state->hand[6][0]);
    assertResult = assert("7th: 2nd Card Estate", estate, state->hand[6][1]);
    assertResult = assert("7th: 3rd Card Estate", estate, state->hand[6][2]);
    assertResult = assert("7th: 4th Card Estate", estate, state->hand[6][3]);

    assertResult = assert("Cards Played", 16, state->playedCardCount);


    assertResult = assertResult + 1;
    printf("\n");
    free(state);
    return 0;
}
