/*
function: getCost(int cardNumber)
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
    int real_result;
	
	printf("*****Unit test for getCost()*****\n");
	real_result = getCost(adventurer);
	if(!assert_result(real_result, 6))
		printf("FAILURE 1: This function is wrong\n");	
	else
		printf("PASS 1: This function is correct\n");

	real_result = getCost(feast);
    if(!assert_result(real_result, 4)) 
        printf("FAILURE 1: This function is wrong\n");  
    else
        printf("PASS 1: This function is correct\n");	
	
	real_result = getCost(curse);
    if(!assert_result(real_result, 0)) 
		printf("FAILURE 1: This function is wrong\n");  
    else
        printf("PASS 1: This function is correct\n");	
	
	printf("*********************************\n");
    return 0;
}

