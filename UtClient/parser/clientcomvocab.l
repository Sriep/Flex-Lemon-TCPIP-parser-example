
%{
#include <cstdio>
#include "clientcomgrammer.h"
#include "clientparse.h"
#define YYSTYPE const char
%}

%option reentrant
%option noyywrap 
%option prefix="yycom"
%option nodefault 
%option header-file="clientcomvocab.yy.h"
%option outfile="clientcomvocab.yy.cpp"
%option bison-bridge
%option extra-type="ClientParse*"
%%
 /* single character ops */


 /* keywords */
"January"   { return JAN; }
"Febuary"	{ return FEB; }
"March"		{ return MAR; }
"April"		{ return APR; }
"May"		{ return MAY; }
"June"		{ return JUN; }
"July"		{ return JUL; }
"August" 	{ return AUG; }
"September"	{ return SEP; }
"October"	{ return OCT; }
"November" 	{ return NOV; }
"December"	{ return DEC; }
"has"		{ return HAS; }
"days"		{ return DAYS; }

[0-9]+	{ yylval = yytext; yyextra->setFlexDays(yytext); return NUM; }

[ \t\r\n]				{ /*White space*/ }
. { /*Skip nonsese*/ }

%%

