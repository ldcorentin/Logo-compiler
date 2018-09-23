#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "structure.h"

FILE* yyin;

/*--------------------------------------------------------         
                 PROGRAM INITIALIZATION
--------------------------------------------------------*/
void initProg (PROG *newProgram)
{
	*newProgram = NULL;
}

/*--------------------------------------------------------         
                CREATE A NEW INSTRUCTION
--------------------------------------------------------*/
INSTR* newStep(int param, int type, int color, INSTR* nextInst, PROG subProgram)
{
	
	INSTR* newStep;
	newStep=(INSTR*)malloc(sizeof(INSTR));
	if(type<1 && type>4)
	{
		newStep = NULL;
	}
	else
	{
		newStep->type=type;
		newStep->param=param;
		newStep->color=color;
		newStep->next=nextInst;
		newStep->subProgram=subProgram;
	}
	return newStep;
}

/*--------------------------------------------------------         
            ADD AN INSTRUCTION TO A PROGRAM
--------------------------------------------------------*/
void addStepToProgram(PROG* pprog, INSTR* stepToAdd)
{
	if(*pprog==NULL) *pprog=stepToAdd;
	else addStepToProgram(&((*pprog)->next), stepToAdd);
}

/*--------------------------------------------------------         
                     COLORATION
association of each number with a color
--------------------------------------------------------*/
char* coloration(int color){
	switch(color) {
		case 1:
			return "BLACK";
			break;
		case 2:
			return "WHITE";
			break;
		case 3:
			return "RED";
			break;
		case 4:
			return "BLUE";
			break;
		case 5:
			return "GREEN";
			break;
		case 6:
			return "YELLOW";
			break;
		default :
			printf("the choosen color isn't define \n");
			exit(0);
			break;
	}
}

/*--------------------------------------------------------         
                     FREE PROGRAM
--------------------------------------------------------*/
void freeLogo(PROG program){
	if(program != NULL)
	{
		freeLogo(program->subProgram);
		freeLogo(program->next);
		free(program);
	}
}

/*--------------------------------------------------------         
                     DISPLAY PROGRAM
--------------------------------------------------------*/
void displayProg(PROG program, int tabulation)
{
	int i;
 
	if (program == NULL) printf("the program is NULL");
	else for(i=0; i<tabulation; i++) printf("\t");
        
	switch(program->type) {
		case 1:
			printf("FORWARD %d %s\n", program->param, coloration(program->color));
			break;
		case 2:
			printf("LEFT %d\n", program->param);
			break;
		case 3:
			printf("RIGHT %d\n", program->param);
			break;     
		case 4:
			printf("REPEAT %d [\n", program->param);
			if(program->subProgram != NULL){
				tabulation++;
				displayProg(program->subProgram, tabulation);
				tabulation--; 
				for(i=0; i<tabulation; i++) printf("\t");
				printf("]\n");                  		
			}                       
			break; 
		case 5:
			printf("CIRCLE %d %s\n", program->param, coloration(program->color));
			break;  
		default:
			printf("Incorrect instruction!\n"); 
			break;
	}
	if(program->next != NULL) displayProg(program->next, tabulation);
	else {
		tabulation = 0;
	}
}

void error(char* message)
{
	printf("ERROR : %s\n", message);
	exit(0);
}


/*--------------------------------------------------------         
                WRITE THE SVG HEADER
--------------------------------------------------------*/
void headerSVG (FILE* logoSVG)
{
	fprintf(logoSVG,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"1000\" height=\"1000\">\n<title>LE DEVEDEC Corentin projet LOGO</title>\n<desc>Du LOGO.</desc>\n");
}


/*--------------------------------------------------------         
                WRITE THE END OF THE SVG
--------------------------------------------------------*/
void endSVG (FILE* logoSVG)
{
	fprintf(logoSVG, "</svg>\n");
	fclose(logoSVG);
}


/*--------------------------------------------------------         
             	       WRITE SVG
--------------------------------------------------------*/
void writeSVG(PROG program, double* x1, double* y1, double* angle, FILE* logoSVG)
{
	int i;
	double x2, y2;
	if(program!=NULL)
	{
	  	if(program->type == 4) for (i = 0; i < (program->param); i++) writeSVG((program->subProgram), x1, y1, angle, logoSVG); //if repeat is in the switch we've got problem
		else {
		  	switch (program->type)
			{
				case 1:
				  	x2=*x1+(double)(cos((M_PI*(*angle))/180.0)*(double)(program->param));
					y2=*y1+(double)(sin((M_PI*(*angle))/180.0)*(double) (program->param));
					fprintf (logoSVG, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />", *x1, *y1, x2, y2, coloration(program->color));
					*x1=x2;
					*y1=y2;
			  	break;
				case 2:
					*angle += (double)(program->param);
			  		break;
				case 3:
			  		*angle -= (double)(program->param);
			  		break;
			  	case 5:
			  		fprintf (logoSVG, "<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"%s\" stroke-width=\"1\" fill=\"none\" />", *x1, *y1, program->param, coloration(program->color));
				default:
			  		break;
		   	}
		}
		  	writeSVG(program->next, x1, y1, angle, logoSVG);
	}
}


/*--------------------------------------------------------         
                     SVG FORM
--------------------------------------------------------*/
void formSVG(PROG program)
{
	double x1 = 500; //the program will start write at the middle of the abscissa axis
	double y1 = 500; //the program will start write at the middle of the abscissa axis
	double angle = 0; //the angle is initialized at 0
	FILE* logoSVG;
	logoSVG = fopen ("logoSVG.svg", "w");
	if(logoSVG == NULL)	exit (1);
	headerSVG(logoSVG);
	writeSVG(program, &x1, &y1, &angle, logoSVG);
	endSVG(logoSVG);
}















