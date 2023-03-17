/*
 * =====================================================================================
 *
 *       Filename:  FSM.h
 *
 *    Description:  FSM结构体头文件
 *
 *        Version:  1.0
 *        Created:  03/29/2018 04:31:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef HEADER_FSM
#define HEADER_FSM

#define MAX_STATE 20

/* 
 * 使用邻接表表示FSM
 */
typedef struct ArcNode{
	struct StateNode* next_state;
	struct ArcNode* next_arc;
	char signal;
} ArcNode;

typedef struct StateNode{
	ArcNode* first_arc;
	int is_final;
	char state;	
} StateNode;

typedef struct FSM{
	int length; //状态的个数
	StateNode* first_state;
	StateNode** states;//动态分配数组
} FSM;

int Init_FSM(FSM*,int);
int Create_Arc(FSM,StateNode*);
int Identify(FSM,char*);
StateNode* Get_Next_State(char,StateNode*);
StateNode* Find_State(FSM,char);


#endif
