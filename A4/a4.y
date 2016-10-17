%{
	#include <stdio.h>
	extern FILE *yyin;
%}

%token MAIN ID DT IF ELSE FOR WHILE NUM RELOP 
%left '+' '-'
%left '*' '/'
%start program

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
program:	MAIN '(' ')' '{' slist '}'		{printf("Program barobar ahe\n");}
			;

slist: vstmt s
		;

vstmt:	varlist vstmt
		|		
		;
varlist: DT vardec ';'						{printf("Valid Declaration\n");}
		;

vardec:	ID ',' vardec
		| ID
		;
s: stmt s
	|	
	;

stmt: ID '=' expr ';'						{printf("Barobar Statemnt ahe\n");}
		|	 expr ';'						{printf("Barobar Statemnt ahe\n");}
		|ifstmt
		|forstmt
		|whilestmt
		;

expr:	expr '+' expr  	{}
	|   expr '-' expr    {}
	|	expr '*' expr 	{}
	|	expr '/' expr 	{}
	|   ID 					{}
	;

condition:	expr RELOP expr
			;

ifstmt: IF '(' condition ')' '{' stmt '}' %prec LOWER_THAN_ELSE					{printf("If statement ahe\n");}
		| IF '(' condition ')' '{' stmt '}' ELSE '{' stmt '}' 					{printf("If and Else statement ahe \n");}
		;


forstmt: FOR '(' assignment ';' condition ';' incdec ')' '{' stmt '}'			{printf("For statement ahe\n");}
			;

assignment:	ID '=' expr	{}
		|	ID '=' NUM	{}
		;

incdec:	ID '+''+'	{}
		|	ID '-''-'	{}
		;


whilestmt: WHILE '('condition ')' '{' stmt '}'									{printf("While statement ahe\n");}
			;

%%

main()
{
	char fname[50];
	printf("Enter File name>>>>\n");		scanf("%s",fname);
	FILE *fp;
	fp=fopen(fname,"r");
	yyin=fp;
	if(!yyparse())		printf("Successful\n");
	else 				printf("Gandla\n");



}

int yyerror(char *err){
	printf("Syntax error");

}

int yywrap()
{
	return 1;
}