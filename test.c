#include <stdlib.h>
#include <stdio.h>
#include "structure.h"


int main()
{

	PROG* pprog    = (PROG*)malloc(sizeof(PROG));
	INSTR *first   = newStep(4,2,0,NULL,NULL);
	INSTR *second  = newStep(10,3,0,NULL,NULL);
	INSTR *eighth  = newStep(9,1,2,NULL,NULL);
	INSTR *test    = newStep(7,3,0,NULL,NULL);
	
	*pprog = first;
	addStepToProgram(pprog, second);
	addStepToProgram(pprog, eighth);
	addStepToProgram(pprog, test);

	printf("the parameter of first is %d and his type is %d\n", first->param, first->type);
	printf("the parameter of first->next is %d and his type is %d\n", (first->next)->param, (first->next)->type);
	printf("the parameter of first->next->next is %d and his type is %d\n", (first->next->next)->param, (first->next->next)->type);

	displayProg(*pprog,0);

	return 0;
}
