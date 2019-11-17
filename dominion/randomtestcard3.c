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

int tribute_funct(struct gameState* state, int currentPlayer, int handPos, int nextPlayer, int tributeRevealedCards[]) {
    int i;
    int cardsToReveal = 2;
    //if not enough cards
    if (state->deckCount[nextPlayer] < cardsToReveal) {
        //at least
        if (state->deckCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deckCount[nextPlayer]--;
            cardsToReveal--;
        }
        //reshuffle
        for (i = 0; i < state->discardCount[nextPlayer]; i++) {
            state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
            state->deckCount[nextPlayer]++;
            state->discard[nextPlayer][i] = -1;
            state->discardCount[nextPlayer]--;
        }
        //Shuffle the deck
        shuffle(nextPlayer,state);

    }

    tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    state->deckCount[nextPlayer]--;
    tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    state->deckCount[nextPlayer]--;

    //if cards the same
    if (tributeRevealedCards[0] == tributeRevealedCards[1]) {
        tributeRevealedCards[1] = -1;
    }
    //Get rewards
    for (i = 0; i < 2; i++) {
        if (tributeRevealedCards[i] >= copper && tributeRevealedCards[i] <= gold) { //Treasure cards
            state->coins += 2;
        }

        else if (tributeRevealedCards[i] >= estate && tributeRevealedCards[i] <= province) { //Victory Card Found
            drawCard(currentPlayer, state);
            drawCard(currentPlayer, state);
        }
        else if (tributeRevealedCards[i] != -1) { //Action Card
            state->numActions = state->numActions + 2;
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
                state->hand[i][j] = tribute;         //Needs tribute to use it
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
        int revealedCards[2] = {-1, -1};
        int result = tribute_funct(state, 0, 0, 1, revealedCards);

        int treasure = 0;
        int victory = 0;
        int action = 0;
        int card1;
        int card2;

        assert("Function exited correctly", 0, result);
        if (copy->deckCount[1] < 2) {
            assert("Other player reshuffled", 2, state->discardCount[1]);
            assert("Other player reshuffled", copy->deckCount[1] + copy->deckCount[1] - 2, state->deckCount[1]);
            card1 = state->discard[1][0];
            card2 = state->discard[1][1];
        }
        else{
            assert("Other player discarded", copy->discardCount[1] + 2, state->discardCount[1]);
            assert("Other player discarded", copy->deckCount[1] - 2, state->deckCount[1]);
            card1 = copy->deck[1][copy->deckCount[1]-1];
            card2 = copy->deck[1][copy->deckCount[1]-2];
        }

        if (card2 == card1) {
            card2 = -1;
        }
        if (card1 >= copper && card1 <= gold) {
                treasure++;
            }
        else if ((card1 >= estate && card1 <= province) || card1 == gardens || card1 == great_hall) {
                victory++;
            }
        else if(card1 != -1){
                action++;
            }
        if (card2 >= copper && card2 <= gold) {
                treasure++;
            }
        else if ((card2 >= estate && card2 <= province) || card2 == gardens || card2 == great_hall) {
                victory++;
            }
        else if(card2 != -1){
                action++;
            }
        assert("Coins gained", copy->coins + 2 * treasure, state->coins);
        assert("Actions gained", copy->numActions + 2 * action, state->numActions);
        assert("Cards drawn", copy->handCount[0] + 2 * victory - 1, state->handCount[0]);
        assert("Card played", 1, state->playedCardCount);


        free(state);
        free(copy);
    }
}


//end of dominion.c