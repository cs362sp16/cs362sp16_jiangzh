/*
discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
*/
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"

int assert_result(int p1, int p2){
    if(p1==p2)
        return 1;
    else
        return 0;
}    

int main(){
	struct gameState g_s;
    int a_cards[10] = {adventurer, council_room, minion, great_hall, cutpurse, mine, gardens, sea_hag, tribute, smithy};	
	int real_result, test_result;   

    printf("\n****Unit test for discardCard()*****\n");
	initializeGame(2, a_cards, 3, &g_s);

	test_result = numHandCards(&g_s);
	discardCard(0, 0, &g_s, 0);
	real_result = numHandCards(&g_s);

	if(!assert_result(real_result, test_result-1))
		printf("FAILURE 1: The function is wrong\n");
	else
		printf("PASS 1: The function is correct\n");		

	printf("*********************************\n");
	return 0;	
}
