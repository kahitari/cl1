%{
	#include "y.tab.h"
%}

%%

[ \t\n]								;
main								{return MAIN;}
int|float|char|long|double			{return DT;}
if 									{return IF;}
else 								{return ELSE;}
for									{return FOR;}
while								{return	WHILE;}
[0-9]+								{return NUM;}
[_a-zA-Z0-9]*						{return ID;}
\<|\>|\=\=|\<\=|\>\=				{return RELOP;}
.									{return yytext[0];}

%%