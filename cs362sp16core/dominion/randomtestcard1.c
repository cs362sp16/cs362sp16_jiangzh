/*
steward: choose 1 actions - draw two cards - gain two coins, give up two cards
*/
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include "math.h"
#include <time.h>

#define TIME_LOOP 2000
int error_list[4];

int assert_result(int p1, int p2){
    if(p1==p2)
        return 1;
    else
        return 0;
}

void checkSteward(struct gameState *g_s, int choice){
    int real_result, test_result1, test_result2;
    
    test_result1 = numHandCards(g_s);    
    test_result2 = g_s->coins;

    real_result = cardEffect(steward, choice, 0, 0, g_s, 0, 0); 
    if(!assert_result(real_result, 0)) 
        error_list[0]++;

    if(choice==1){
        real_result = numHandCards(g_s);
        if(!assert_result(real_result, test_result1+2-1))
            error_list[1]++;
    } 
    else if(choice==2){
        real_result = g_s->coins;
        if(!assert_result(real_result, test_result2+2))
            error_list[2]++;
    }
    else{
        real_result = numHandCards(g_s); 
        if(!assert_result(real_result, test_result1-2-1))
            error_list[3]++;
    }    
}

int main(int argc, char* argv[]){
    struct gameState g_s;
    int a_cards[10] = {adventurer, steward, minion, village, cutpurse, mine, gardens, sea_hag, tribute, smithy};
    int i, j, n, p, seed, number_player, choice;
    
	printf("\n***** Random test for steward *****\n");
	srand(time(NULL));    
    
	for(i=0; i<4; i++)
        error_list[i] = 0;

    if(argv[1]!=NULL)
        seed = atoi(argv[1]);
    else
        seed = rand()%10 + 1;

    for(n=0; n<TIME_LOOP; n++){
        for(i=0; i<sizeof(struct gameState); i++){
            ((char*)&g_s)[i] = floor(Random() * 256);
        }   
        number_player = rand()%3+2;
		initializeGame(number_player, a_cards, seed, &g_s);
        p = rand()%number_player;
        g_s.whoseTurn = p;
        choice = rand()%3;

        g_s.deckCount[p] = rand()%(MAX_DECK + 1);
        for(j=0; j<g_s.deckCount[p]; j++)
            g_s.deck[p][j] = rand()% treasure_map;

        g_s.discardCount[p] = floor(Random() * MAX_DECK);
        for (j = 0; j < g_s.discardCount[p]; j++)
            g_s.discard[p][j] = rand() % treasure_map;
        
        g_s.handCount[p] = floor(Random() * MAX_HAND);
        g_s.hand[p][0] = steward;
        for (j = 1; j < g_s.handCount[p]; j++)
            g_s.hand[p][j] = rand() % treasure_map;
	
        checkSteward(&g_s, choice);
    }
    printf("Error  Time\n");
    for(i=0; i<4; i++)
        printf("%d       %d\n", i+1, error_list[i]);
    printf("******** Random test done ********\n");
    return 0;

}
 
