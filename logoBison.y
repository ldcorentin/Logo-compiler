%{
/*---------------------------------------------------------

             TP AGP : compilateur TC LOGO
             synatxique d'une expression reguliere

                       Le Devédec Corentin
                         /2017

---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "structure.h"

/*--------------------------------------------------------         
                  FONCTIONS LEX/YACC
--------------------------------------------------------*/
int yyerror()
{
	error("parsing error");
	exit(1);
}

int yywrap()
{
	return 1;
}

%}


//token list
%token TFORWARD	
%token TLEFT
%token TRIGHT
%token TCIRCLE
%token TREPEAT
%token TCOLOR
%token TBEGIN
%token TEND
%token TPARAM


//declaration of types
%union
{
	INSTR* INSTRUCTION_TYPE;
	PROG PROGRAM_TYPE;
	int INT_TYPE;
};

//type of yylval
%type <INT_TYPE> 	 TPARAM
%type <INT_TYPE> 	 TCOLOR
%type <PROGRAM_TYPE> 	 TPROG
%type <INSTRUCTION_TYPE> TINSTR


%%
TPROG : TINSTR
	{	
			$$ = $1;
			root = $$;
	}
	| TPROG TINSTR
	{
		addStepToProgram(&$1, $2);
		$$ = $1;
		root = $$;
	}

TINSTR : TFORWARD TPARAM TCOLOR
		{$$ = newStep($2, 1, $3, NULL, NULL);}

	|TFORWARD TPARAM
		{$$ = newStep($2, 1, 1, NULL, NULL);}
	
	|TLEFT TPARAM
		{$$ = newStep($2, 2, 0, NULL, NULL);}
	
	|TRIGHT TPARAM
		{$$ = newStep($2, 3, 0, NULL, NULL);}

	|TCIRCLE TPARAM TCOLOR
		{$$ = newStep($2, 5, $3, NULL, NULL);}

	|TCIRCLE TPARAM 
		{$$ = newStep($2, 5, 1, NULL, NULL);}

	|TREPEAT TPARAM TBEGIN TPROG TEND
		{$$ = newStep($2, 4, 0, NULL, $4);}
	
%%


/*------------------------------------------------------         
                        MAIN

               Call to function yyparse()
--------------------------------------------------------*/
int main()
{
	char* c;
	char* control;

	control = "y";

	yyparse();
	formSVG(root);
	displayProg(root,0);
	freeLogo(root);

	/*printf("Do you want to open the SVG image ? [y/n]\n");
	scanf("%s\n", &c);
	if(strcmp(c,control)==0)	system("eog logoSVG.svg");
	else				printf("I'm sad you don't want to see this beautiful image\n");*/

	system("eog logoSVG.svg");

	return 0;	
}








