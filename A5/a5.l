%{
	#include "y.tab.h"
	#include <stdio.h>
	#include <string.h>
%}

%%
[ \t\n]+											;

main												{return MAIN;}
int|float|char|double|long							{strcpy(yylval.sval,yytext); return DT;}
[a-zA-Z][a-zA-Z0-9_]*								{strcpy(yylval.sval,yytext); return 	ID;}
[0-9]+												{strcpy(yylval.sval,yytext); return NUMBER;}
. 													{return yytext[0];}
%%


