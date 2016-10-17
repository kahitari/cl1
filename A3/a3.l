%{
	#include <string.h>

	int insert(char str[]);
	int insert_error(char str_error[]);
	char c1[50],c2[50];
	FILE *fin,*fout;
	unsigned int count=0,count_error=0,n=1,i,j;

	struct symbol_table
	{
		char name[50];
		int value;

	}*symbol[50];

	struct error_table
	{
		char error_ala[50];
		int kai_ala;

	}*error[50];

%}

%%

[ \t]+		;

[\n]+		{ n++;}

\/\*.*\*\/[ \t\n]*		{n++;}

\/\/.*[ \t\n]*			{n++;}

\/\*[_a-zA-Z]+			{printf("\n%d\t%s\t\t Unidentified Comment \t%d",n,yytext,insert_error(yytext));}

#						{printf("\n%d\t # \t\t  Preproecssor",n);}

include					{printf("\n%d\t Include \t\t Keyword",n);}

\<						{printf("\n%d\t Less than \t",n);}

\>						{printf("\n%d\t Greater than \t",n);}

[a-zA-Z0-9]+\.h			{printf("\n%d\t%s\t Header \t",n,yytext);}

\( 						{printf("\n%d\t ( \t\t Left Bracket",n);}

\) 						{printf("\n%d\t ) \t\t Right Bracket",n);}

\{						{printf("\n%d\t { \t\t Opening Brace",n);}

\}						{printf("\n%d\t } \t\t Closing Brace",n);}

\,						{printf("\n%d\t , \t\t Comma",n);}

\;						{printf("\n%d\t ; \t\t End of Statement",n);}

\=|\+|\-|\*|\/			{printf("\n%d\t%s\t\t  Operator \t",n,yytext);}

void|short|long|int|float|char|double|struct|class		{printf("\n%d\t%s\t\t DataType \t",n,yytext);}

main|printf|scanf		{printf("\n%d\t%s\t\t  Built in Function \t\t",n,yytext);}

\"[ _a-zA-Z0-9\%\-\\]*\"	{printf("\n%d\t%s\t\t String Constant",n,yytext);}

\'[ _a-zA-Z0-9]\'			{printf("\n%d\t%s\t\t Character Constant",n,yytext);}

[0-9]+						{printf("\n%d\t%s\t\t Integer Constant",n,yytext);}

([_a-zA-Z]+[_a-zA-Z0-9]*)	{printf("\n%d\t%s\t\t Identifier \t%d",n,yytext,insert(yytext));}

\"[_a-zA-Z]*				{printf("\n%d\t%s\t\t Unidentified Delimiter \t%d",n,yytext,insert_error(yytext));}

[0-9]+[_a-zA-Z]+			{printf("\n%d\t%s\t\t Unidentified Token \t%d",n,yytext,insert_error(yytext));}


%%

main()
{
	printf("\nInput File>>>>>>");		scanf("%s",c1);
	printf("\n Output File>>>>>>");		scanf("%s",c2);

	fin=fopen(c1,"r");
	fout=fopen(c2,"w");

	yyin=fin;
	yyout=fout;

	printf("\n Line no \t Lexeme \t Token \t Attribute");

	printf("\n");
	
	yylex();

	printf("\n Symbol Table");

	for(int i=0;i<count;i++) printf("\n%s\t%d",symbol[i]->name,symbol[i]->value);

	printf("\n");
	printf("\n Error Table:");

	for(int j=0;j<count_error;j++)	printf("\n%s\t%d\n",error[j]->error_ala,error[j]->kai_ala);

		fclose(fin);
		fclose(fout);

}

int insert(char str[])
{
	int i;
	for(i=0;i<count;i++)
	{
		if(strcmp(str,symbol[i]->name)==0)
		{
			symbol[i]->value+=1;
			return i;
		}

	}

	symbol[count]=(struct symbol_table*)malloc(sizeof(struct symbol_table));

	strcpy(symbol[count]->name,str);
	return count++;
}

int insert_error(char  str_error[])
{
	int j;
	for(j=0;j<count_error;j++)
	{
		if(strcmp(str_error,error[j]->error_ala)==0)  return j;
	}

	error[count_error]=(struct error_table*)malloc(sizeof(struct error_table));

	strcpy(error[count_error]->error_ala,str_error);
	error[count_error]->kai_ala;
	return count_error++;
}

int yywrap()
{
	return 1;
}
