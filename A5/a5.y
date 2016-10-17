%{
	#include "stdio.h"
	#include "string.h"

	extern FILE* yyin;

	struct tbl_row{
		char type[50];
		char val[50];
	}sym_tbl[50];

	struct quad_row{
		char op1[50];
		char op2[50];
		char res[50];
		char op;
	}quad_tbl[50];

	int sym_index=0;
	int quad_index=0;

	struct stack_item{
		char	item[50];
	}stack[50];

	int top=-1;

	int temp_index=0;

	void InsertintoSymbol_table(char*,char*);
	void InsertintoQuad_table(char*,char*,char*,char);
	void push(char*);

	char* pop();
%}

%union
{
	char sval[20];
}

%token MAIN

%token <sval> ID
%token <sval> NUMBER
%token <sval> DT

%left '+' '-'
%left '*' '/'

%start program

%%
program:	MAIN '(' ')' '{' slist '}'		{ printf("Program barobar ahe \n"); }
			;

slist: vstmt s
		;

vstmt:	varlist vstmt
		|		
		;
varlist: DT vardec ';'						
		;

vardec:	ID ',' vardec					{ InsertintoSymbol_table($1,"0"); }
		| ID '=' NUMBER ',' vardec		{ InsertintoSymbol_table($1,$3); }
		| ID '=' NUMBER					{ InsertintoSymbol_table($1,$3); }
		| ID 							{ InsertintoSymbol_table($1,"0"); }
		;
s: stmt s
	|	
	;

stmt: ID '=' expr ';'						{InsertintoQuad_table(pop()," ",$1,'=');}
		|	 expr ';'						
		;

expr:	expr '+' expr  		{	
									char temp[4];
									sprintf(temp,"\t%d",temp_index);
									InsertintoQuad_table(pop(),pop(),temp,'+');
									push(temp);
									temp_index++;
		
							}
	|   expr '-' expr    {	
									char temp[4];
									sprintf(temp,"\t%d",temp_index);
									InsertintoQuad_table(pop(),pop(),temp,'-');
									push(temp);
									temp_index++;	


						}

	|	expr '*' expr 		{

									char temp[4];
									sprintf(temp,"\t%d",temp_index);
									InsertintoQuad_table(pop(),pop(),temp,'*');
									push(temp);
									temp_index++;			


							}


	|	expr '/' expr 		{

									char temp[4];
									sprintf(temp,"\t%d",temp_index);
									InsertintoQuad_table(pop(),pop(),temp,'/');
									push(temp);
									temp_index++;
							}


	|   ID 					{push($1);}

	|   NUMBER 				{push($1);}
	;

%%

int yyerror(char *st)
{
	printf("Syntax Errror\n");
}	

int main()
{
		FILE* fp=fopen("in.c","r");
		yyin=fp;
		yyparse();

		int i=0,j;

		printf("\n Symbol Table \n");

		for(i=0;i<sym_index;i++)  printf("%s\t\t%s\n",sym_tbl[i].type,sym_tbl[i].val);

		printf("\n Quadruple Table \n");

		for(j=0;j<quad_index;j++)	printf("%s\t\t%s\t\t%s\t\t%c\n",quad_tbl[j].op1,quad_tbl[j].op2,quad_tbl[j].res,quad_tbl[j].op);

		fclose(fp);
		return 0;
	
}


void InsertintoQuad_table(char* op1, char* op2, char* res, char op) {
	struct quad_row q;
	strcpy(q.op1,op1);
	strcpy(q.op2,op2);
	strcpy(q.res,res);
	q.op=op;
	quad_tbl[quad_index]=q;
	quad_index++;
}

void InsertintoSymbol_table(char* type,char* val)
{
	struct tbl_row t;
	strcpy(t.type,type);
	strcpy(t.val,val);
	sym_tbl[sym_index]=t;
	sym_index++;
}

void push(char* s)
{
	struct stack_item obj;
	strcpy(obj.item,s);
	stack[++top]=obj;
}

char* pop()
{
	char* str=stack[top--].item;
	return str;
}

int yywrap()
{
	return 1;
}								

