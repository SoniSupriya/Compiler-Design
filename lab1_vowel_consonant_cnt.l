%{
#include<stdio.h>
#include<string.h>
int vowels=0;
int cons=0;
%}

%%
[aeiouAEIOU] {vowels++;}
[a-zA-Z] {cons++;}
%%

int yywrap()

{
return 1;
}
int main()
{
printf("Enter the string.. at end press ^d\n");
yylex();
printf("No of vowels=%d\nNo of consonants=%d\n",vowels,cons);
}
