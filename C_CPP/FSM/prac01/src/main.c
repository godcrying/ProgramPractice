/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  FSM有限状态机练习
 *
 *        Version:  1.0
 *        Created:  03/26/2018 04:32:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "FSM.h"

int main()
{
	FSM F;
	Init_FSM(&F,4);
	printf("自动机的状态图：\n");
	for(int i=0;i<F.length;i++){
		printf("%c ",F.states[i]->state);
		ArcNode* tmp = F.states[i]->first_arc;
		while(tmp != NULL){
			printf("%c->%c ",tmp->signal,\
					tmp->next_state->state);
			tmp = tmp->next_arc;
		}
		printf("\n");
	}
	if(Identify(F,"ababaaa"))
		printf("Identified string 'ababaaa'\n");
	if(!Identify(F,"abcdaaa"))
		printf("can't identify string 'abcdaaa'\n");


	return 0;	
}
