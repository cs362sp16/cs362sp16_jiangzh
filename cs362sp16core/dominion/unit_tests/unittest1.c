/*
function: getCost(int cardNumber)
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
    int gain_result;
	
	gain_result = getCost(adventurer);
	if(!assert_result(gain_result, 6))
		printf("Failure");


	gain_result = getCost(feast);
    if(!assert_result(gain_result, 4)) 
        printf("Failure");

	gain_result = getCost(curse);
    if(!assert_result(gain_result, 0)) 
        printf("Failure");
	
    return 0;
}

