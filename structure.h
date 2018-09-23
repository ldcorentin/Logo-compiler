#ifndef structure_h_
#define structure_h_


#include <stdlib.h>
#include <stdio.h>


struct model_instruction {
	int type;
	int param;
	int color;
	struct model_instruction* next;
	struct model_instruction* subProgram;
};
typedef struct model_instruction INSTR;
typedef INSTR* PROG;

PROG root;

INSTR* newStep(int param, int type, int color, INSTR* nextInst, PROG subProgram);
void addStepToProgram(PROG* program, INSTR* stepToAdd);
char* coloration(int color);
void displayProg(PROG program, int tabulation);
void error(char* message);
void initProg (PROG *newProgram);
void formSVG (PROG program);
void headerSVG (FILE* logoSVG);
void writeSVG(PROG program, double* x1, double* y1, double* angle, FILE* logoSVG);
void endSVG (FILE* logoSVG);
void freeLogo(PROG program);


#endif
