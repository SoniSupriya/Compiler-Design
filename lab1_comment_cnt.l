%{
#include<stdio.h>
#include<string.h>
int com=0;
%}

%s COMMENT

%%
"/*"              { BEGIN(COMMENT); com++; }
<COMMENT>"*/"      { BEGIN(INITIAL); }
<COMMENT>\n        { com++; }
<COMMENT>.         { /* consume everything inside comment */ }
<COMMENT><<EOF>>   { /* unclosed comment */ BEGIN(INITIAL); }
.|\n               { fprintf(yyout, "%s", yytext); }
%%

int yywrap()
{
return 1;
}

int main(int argc, char *argv[])
{
if(argc!=3)
{
printf("Usage: %s <inputfile> <outputfile>\n", argv[0]);
exit(1);
}
yyin=fopen(argv[1],"r");
yyout=fopen(argv[2],"w");
yylex();
printf("No of comment lines=%d\n",com);
}

