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
                state->hand[i][j] = baron;         //Needs baron to use it
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

    int blank;        //cardEffect wants an int* bonus that is unused
    int i;
    for(i = 0; i < 50000; i++){
        struct gameState* state = random_state();
        struct gameState* copy = copy_state(state);
        int choice = rand() % 2;
        int result = cardEffect(baron, choice, 0, 0, state, 0, &blank);
        //int result = baron_funct(state, 0, 0, choice);

        assert("Function exited correctly", 0, result);
        assert("Buys incremented correctly", copy->numBuys + 1, state->numBuys);

        if (choice == 0 || (choice == 1 && !cardInHand(copy, 0, estate))) {      //Gain Estate
            printf("------Gain Estate------\n");
            assert("No coins gained", copy->coins, state->coins);
            assert("Baron card removed", copy->handCount[0] - 1, state->handCount[0]);
            assert("Estate card remained", cardInHand(copy, 0, estate), cardInHand(state, 0, estate));
            assert("Card gained", copy->discardCount[0] + 1, state->discardCount[0]);
            assert("Estate Card gained", estate, state->discard[0][state->discardCount[0] - 1]);
            assert("Card played", 1, state->playedCardCount);
            assert("Baron Card played", baron, state->playedCards[0]);
        }
        else {                                                                        //Discard Estate
            printf("------Discard Estate------\n");
            assert("4 coins gained", copy->coins + 4, state->coins);
            assert("Baron and Estate card removed", copy->handCount[0] - 2, state->handCount[0]);
            assert("Card played", 1, state->playedCardCount);
            assert("Baron Card played", baron, state->playedCards[0]);
        }
        free(state);
        free(copy);
    }
}


//end of dominion.c
