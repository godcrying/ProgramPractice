/*
 * =====================================================================================
 *
 *       Filename:  FSM.c
 *
 *    Description:  FSM方法定义
 *
 *        Version:  1.0
 *        Created:  03/29/2018 04:53:09 PM
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

int Init_FSM(FSM* F,int n){
	//创建所有state节点，并确定初始节点
	F->states = (StateNode**)malloc(n*sizeof(StateNode*));
	if(!F->states) return -1;
	//分成三部分：初始，非终止，终止
	char c;int index=0;
	StateNode** states = F->states;
	printf("请输入初始状态：\n");
	while((c=getchar()) != '\n'){
		if(index >= n){
			break;
		}
		if(c == ' ') continue;
		states[index] = (StateNode*)malloc(sizeof(StateNode));
		if(!states[index]) return -1;
		
		states[index]->is_final=0;
		states[index]->state = c;
		states[index]->first_arc=NULL;
		F->first_state = states[index];

		index++;
	}
	printf("请输入非终止状态：\n");
	while((c=getchar()) != '\n'){
		if(index >= n){
			break;
		}
		if(c == ' ') continue;
		states[index] = (StateNode*)malloc(sizeof(StateNode));
		if(!states[index]) return -1;
		
		states[index]->is_final = 0;
		states[index]->state = c;
		states[index]->first_arc=NULL;
		index++;
	}
	printf("请输入终止状态：\n");
	while((c=getchar()) != '\n'){
		if(index >= n){
			break;
		}
		if(c == ' ') continue;
		states[index] = (StateNode*)malloc(sizeof(StateNode));
		if(!states[index]) return -1;
		
		states[index]->is_final = 1;
		states[index]->state = c;
		states[index]->first_arc=NULL;
		index++;
	}

	F->length = n;

	//从FSM.states第一个元素开始，构造Arc
	//初始化Arc的next_state时需要根据state名称遍历FSM.states进行查询
	//
	for(int i=0;i<n;i++){
		Create_Arc(*F,F->states[i]);
	}
	
		return 0;
}

int Create_Arc(FSM F,StateNode* node)
{
	char buffer[5],c;
	char* pointer=buffer;//buffer的真正的指针
	int set_first_arc=0;//方便赋值节点的第一个Arc

	ArcNode* last_arc=NULL;
	printf("输入状态%c的Arc，格式:(a,A),以空格分隔:\n",node->state);
	while((c=getchar()) != '\n'){
		if(c == ' ') continue;
		*pointer=c;
		pointer++;

		if(c == ')'){
			//当读取到")"时，将栈内的数据生成一个边
			ArcNode* arc = (ArcNode*)malloc(sizeof(ArcNode));
			if(!arc) return -1;
			arc->next_arc = NULL;

			arc->signal = buffer[1];
			arc->next_state = Find_State(F,buffer[3]);

			if(!set_first_arc){
				node->first_arc = arc;
				last_arc = arc;
				set_first_arc = 1;
			}else{
				last_arc -> next_arc = arc;
				last_arc = arc;
			}
			pointer = buffer;//清空栈（也就是初始化栈指针）

		}//if
	}//while
	return 0;
}

StateNode* Find_State(FSM F, char state)
{
	//在生成边Arc时，要寻找下一个state
	for(int i=0;i<F.length;i++){
		if(F.states[i]->state == state)
			return F.states[i];
	}
	return NULL;
}

int Identify(FSM F,char* s)
{

	char* c=s;
	StateNode* last_state = F.first_state;
	while( *c != '\0'&& last_state != NULL){
		//！！千万注意，不要向NULL变量使用"->"运算符
		//否则会出现
		//根据输入符号c，获取下一个状态
		last_state = Get_Next_State(*c,last_state);
		c++;
	}
	if(last_state && last_state->is_final == 1)
		return 1;
	return 0;
}

StateNode* Get_Next_State(char c,StateNode* state)
{
	ArcNode* arc = state->first_arc;
	while(arc){//从第一个Arc开始遍历
		if(c == arc->signal)
			return arc->next_state;
		arc = arc->next_arc;
	}
	return NULL;
}
