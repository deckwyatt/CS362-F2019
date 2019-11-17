#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int assert(char* test, int target, int variable) {
    if (target != variable) {
        printf("TEST FAILED: '%s', Wanted: %d, GOT: %d\n", test, target, variable);
        return 0;
    }
    /*else {
        printf("SUCCESS: %s\n", test);
        return 1;
    }*/
    return 1;
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

struct gameState* random_state() {
    struct gameState* state = newGame();
    int i, j;

    state->numPlayers = (rand() % 3) + 2;         //2-4 players
    state->whoseTurn = 0;                         //Non-inputs
    state->numActions = 0;                        //  |
    state->coins = 0;                             //  |
    state->numBuys = 0;                           //  |
    for(i = 0; i < state->numPlayers; i++){       //Fill hands and decks
        state->handCount[i] = rand() % 6 + 1;
        for(j = 0; j < state->handCount[i]; j++){
            if (i == 0 && j == 0) {
                state->hand[i][j] = minion;         //Needs card to use it
            }
            else{
                state->hand[i][j] = rand() % (treasure_map + 1);
            }
        }
        state->deckCount[i] = rand() % 30;
        for(j = 0; j < state->deckCount[i]; j++){
            state->deck[i][j] = rand() % (treasure_map + 1);
        }
        state->discardCount[i] = rand() % 30;
        for(j = 0; j < state->discardCount[i]; j++){
            state->discard[i][j] = rand() % (treasure_map + 1);
        }
    }
    state->playedCardCount = 0;

    return state;
}
struct gameState* copy_state(struct gameState* original) {
    struct gameState* state = newGame();
    int i, j;

    state->numPlayers = original->numPlayers;
    for(i = 0; i < treasure_map+1; i++){
        state->supplyCount[i] = original->supplyCount[i];
        state->embargoTokens[i] = original->embargoTokens[i];
    }
    state->outpostPlayed = original->outpostPlayed;
    state->outpostTurn = original->outpostTurn;
    state->whoseTurn = original->whoseTurn;
    state->phase = original->phase;
    state->numActions = original->numActions;
    state->coins = original->coins;
    state->numBuys = original->numBuys;
    for(i = 0; i < MAX_PLAYERS; i++){
        state->handCount[i] = original->handCount[i];
        for(j = 0; j < MAX_HAND; j++){
            state->hand[i][j] = original->hand[i][j];
        }
        state->deckCount[i] = original->deckCount[i];
        state->discardCount[i] = original->discardCount[i];
        for(j = 0; j < MAX_DECK; j++){
            state->deck[i][j] = original->deck[i][j];
            state->discard[i][j] = original->discard[i][j];
        }
    }
    for(i = 0; i < MAX_DECK; i++){
        state->playedCards[i] = original->playedCards[i];
    }
    state->playedCardCount = original->playedCardCount;

    return state;
}

int cardInHand(struct gameState* state, int player, int card) {
    int i;
    for(i = 0; i < state->handCount[player]; i++){
        if (state->hand[player][i] == card) {
            return 1;
        }
    }
    return 0;
}
int cardInDeck(struct gameState* state, int player, int card) {
    int i;
    for(i = 0; i < state->deckCount[player]; i++){
        if (state->deck[player][i] == card) {
            return 1;
        }
    }
    return 0;
}
int cardInDiscard(struct gameState* state, int player, int card) {
    int i;
    for(i = 0; i < state->discardCount[player]; i++){
        if (state->discard[player][i] == card) {
            return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(0));

    int i;
    for(i = 0; i < 50000; i++){
        struct gameState* state = random_state();
        struct gameState* copy = copy_state(state);
        int choice1 = rand() % 2;
        int choice2;
        if (choice1) {
            choice2 = 0;
        }
        else {
            choice2 = 1;
        }
        int result = minion_funct(state, 0, 0, choice1, choice2);



        assert("Function exited correctly", 0, result);
        assert("Action gained", copy->numActions + 1, state->numActions);
        if (choice1 == 1) {
            assert("2 coins gained", copy->coins + 2, state->coins);
            assert("Minion card removed", copy->handCount[0] - 1, state->handCount[0]);
            assert("Card played", 1, state->playedCardCount);
            assert("Minion Card played", minion, state->playedCards[0]);
        }
        else if(choice2){
            int j;
            int count = 0;

            assert("No coins gained", copy->coins, state->coins);
            assert("Hand Wheeled", 4, state->handCount[0]);
            assert("Card played", 1, state->playedCardCount);
            assert("Minion Card played", minion, state->playedCards[0]);

            count += copy->handCount[0];
            assert("Player Redrew", 4, state->handCount[0]);
            for(j = 1; j < state->numPlayers; j++){
                if (copy->handCount[j] >= 5) {
                    count += copy->handCount[j];
                    assert("Player Redrew", 4, state->handCount[j]);
                }
                else {
                    assert("Player Didn't Redrew", copy->handCount[j], state->handCount[j]);
                }
            }

            assert("Cards Played", count, state->playedCardCount);
        }

        free(state);
        free(copy);
    }
}


//end of dominion.c
