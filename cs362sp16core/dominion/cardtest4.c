/*
great hall: gain one card and on action card
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
    int test_result1, real_result;   

    printf("\n*****Card test for great hall*****\n");
    initializeGame(2, a_cards, 3, &g_s);

    test_result1 = numHandCards(&g_s);    
    real_result = cardEffect(great_hall, 0, 0, 0, &g_s, 0, 0);  

	if(!assert_result(real_result, 0)) 
         printf("FAILURE 1:  This card cannot be executed\n");
    else{
		printf("PASS 1: This card can be executed\n");

    	real_result = numHandCards(&g_s);
    	if(!assert_result(real_result, test_result1+1-1))
			 printf("Failure 2:  The effact of this card is incorrect\n");   
        else
            printf("PASS 2: The effact of this card is correct\n");
	}
	printf("*********************************\n");
	return 0;
}
