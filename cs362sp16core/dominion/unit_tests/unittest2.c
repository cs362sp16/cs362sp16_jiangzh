/*
fullDeckCount(int player, int card, struct gameState *state)
*/
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominon.h"
#include "assert.h"
#include "dominion_helpers.h"

int assert_result(int p1, int p2){
    if(p1==p2)
        return 1;
    else
        return 0;
}    

int main(int argc char** argv){

struct gameState g_s;
    int a_cards[10] = {adventurer, council_room, minion, great_hall, cutpurse, mine, gardens, sea_hag, tribute, smithy};
    int real_result;   

    printf("Unit test for \n");
    initializaGame(2, a_cards, 3, &g_s);

	gain_result = fullDeckCount(0, 0, &g_s);
	
	if(!assert(gain_result, 10))
		printf("Failure");

	return 0
}
