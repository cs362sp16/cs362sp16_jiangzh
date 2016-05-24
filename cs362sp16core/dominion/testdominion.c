#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include "math.h"
#include <time.h>

#define TEST_NUM 1000

int check_kingdomcard(int *r_kingdomcard, int i){
	int j;
	for(j=0; j<i; j++){
		 if(r_kingdomcard[i]==r_kingdomcard[j])
				return 1;
	}
	return 0;
}

int check_num_action(struct gameState *g){
	int i, num=0, whose;
	whose = g->whoseTurn;

	for(i=0; i<numHandCards(g); i++)
		if(g->hand[whose][i] >= adventurer && g->hand[whose][i] <= treasure_map)
				num++;

	return num;
}

int check_money(struct gameState *g){
	int i, money=0;
	for(i = 0; i < numHandCards(g); i++){			
    	if(handCard(i, g)==copper)
   	 		money++;
   	   	else if(handCard(i, g)==silver)
    		money += 2;
    	else if(handCard(i, g)==gold)
    		money += 3;
    	else
   	 		money += 0;
   	}
   	return money;
}

void generate_choice(struct gameState *g, int card, int* choice1, int* choice2, int* choice3){
	if(card==mine || card==remodel){
		*choice1 = rand()%(numHandCards(g));
		*choice2 = rand()%(numHandCards(g));
		*choice3 = -1;
	}
	else if(card==feast){
		*choice1 = rand()%27;
		*choice2 = -1;
		*choice3 = -1;		
	}
	else if(card==baron){
		*choice1 = rand()%2;
		*choice2 = -1;	
		*choice3 = -1;
	}
	else if(card==minion){
		*choice1 = rand()%2;
		if(*choice1==1)
			*choice2 = 0;
		else
			*choice2 = 1;
		 *choice3 = -1;
	}
	else if(card==steward){
		*choice1 = rand()%3;
		*choice2 = 0;
		*choice3 = 0;
	}
	else if(card==embargo){
		*choice1 = rand()%10;
		*choice2 = 1;
		*choice3 = 0;
	}
	else if(card==cutpurse){
		*choice1 = rand()%27;
		*choice2 = -1;
		*choice3 = -1;
	}
	else if(card==salvager){
		*choice1 = rand()%2;
		*choice2 = -1;
		*choice3 = -1;
	}
	else{
		*choice1 = -1;
		*choice2 = -1;
		*choice3 = -1;
	}
}

void random_kingdomcard(int *r_kingdomcard){
	int i;
	
	r_kingdomcard[0]=rand()%(treasure_map - 7 + 1) + 7;
	
	for(i=1; i<10; i++){
		do{
			r_kingdomcard[i]=rand()%(treasure_map - 7 + 1) + 7; 
		}
		while(check_kingdomcard(r_kingdomcard, i));
	}
}

void print_game_information(struct gameState *g, int *kingdom_cards, int seed){
    int i;
    
	printf("\n******Information of Game********\n");
	
	printf("The seed is %d\n", seed);
    printf("Number of Player: %d\n", g->numPlayers);
    printf("Kingdom Cards: \n");
    for(i=0; i<5; i++)
        printf("%d ", kingdom_cards[i]);
    printf("\n");
    for(i=5; i<10; i++)
        printf("%d ", kingdom_cards[i]);
	printf("\n");
	
	printf("*********Game Begins**********\n");
}

void random_initialize(int seed, struct gameState *g){
	int r_num_player, r_kingdomcard[10];

	SelectStream(1);
	PutSeed(seed);

	r_num_player = rand()%2+2;
	random_kingdomcard(r_kingdomcard);
	
	initializeGame(r_num_player, r_kingdomcard, (int)seed, g);
	print_game_information(g, r_kingdomcard, seed);
}


void perform_actions(struct gameState *g){
	int handPos=0, gainCard, result=1;
	int handCount = numHandCards(g);
	int choice1, choice2, choice3;
	
	if(check_num_action(g)>0){
		do{
			handPos = rand()%handCount;
			gainCard = g->hand[g->whoseTurn][handPos];
			if(gainCard >= adventurer && gainCard <= treasure_map) 
				result = 0;
		}while(result==1);
	

		generate_choice(g, gainCard, &choice1, &choice2, &choice3);		
		playCard(handPos, choice1, choice2, choice3, g);
		printf("Player %d: played %d\n", g->whoseTurn+1, gainCard);
	}

	else
		printf("Player %d: skip play phase\n", g->whoseTurn+1);
}

void perform_buys(struct gameState *g){
	int gainCard, i, index, size=0, money=check_money(g);
	int remain_supply[treasure_map+1];

	
	for(i=0; i<treasure_map+1; i++){
		if(money >= getCost(i) && supplyCount(i, g)>0){
			remain_supply[size] = i;
			size++;
		}
	}

	if(size>0){
		index = rand()%size;
		gainCard = remain_supply[index];

		if(buyCard(gainCard, g)==0)
			printf("Player %d: bought %d\n", g->whoseTurn+1, gainCard);
	}
}

void end_turn(struct gameState *g){
	printf("Player %d: end turn\n", g->whoseTurn+1);
	endTurn(g);
}

void print_result(struct gameState *g){
	int i, players[g->numPlayers];

	printf("\n********Game Over**********\n");

	for(i=0; i<g->numPlayers; i++)
		printf("Player %d: %d\n", i+1, scoreFor(i, g));
	
	getWinners(players, g);
	
	for(i=0; i<g->numPlayers; i++)
		if(players[i]==1)
			printf("Player %d is the winner\n", i+1);
}

void random_game(int seed){
	struct gameState g;

	random_initialize(seed, &g);	
	while(!isGameOver(&g)){
		perform_actions(&g);
		perform_buys(&g);
		end_turn(&g);
	}
	print_result(&g);
}

int main(int argc, char* argv[]){
	int i, seed;
		
	srand(time(NULL));
	if(argv[1]!=NULL)
		seed = atoi(argv[1]);
	else
		seed = rand()%10 + 1;
	
	for(i=0; i<TEST_NUM; i++)
		random_game(seed);
	
	return 0;
}
