%{
#include <stdio.h>
#include "structure.h"
#include "logoBison.tab.h"
%}

%%
[0-9]* 		{yylval.INT_TYPE = atoi(yytext); return TPARAM;} 
"FORWARD" 	{return TFORWARD;}
"LEFT" 		{return TLEFT;}
"RIGHT" 	{return TRIGHT;}
"REPEAT" 	{return TREPEAT;}
"CIRCLE"	{return TCIRCLE;}
"["		{return TBEGIN;}
"]"		{return TEND;}
"BLACK"      	{yylval.INT_TYPE = 1; return TCOLOR;}
"WHITE"		{yylval.INT_TYPE = 2; return TCOLOR;}
"RED"		{yylval.INT_TYPE = 3; return TCOLOR;}
"BLUE"		{yylval.INT_TYPE = 4; return TCOLOR;}
"GREEN"		{yylval.INT_TYPE = 5; return TCOLOR;}
"YELLOW"	{yylval.INT_TYPE = 6; return TCOLOR;}
\n		/*ignore end of line*/;
[ t]+		/*ignore whitespace*/;
%%


