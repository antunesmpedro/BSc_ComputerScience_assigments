%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIV; }
"=" { return ATR; }
"==" { return EQUALS; }
"!=" { return DIFF; }
">" { return GREAT; }
"<" { return LESS; }
">=" { return GREATEQ; }
"<=" { return LESSEQ; }
"if" { return IF; }
"else" { return ELSE; }
"for" { return FOR; }
"while" { return WHILE; }
"{" { return OPENB; }
"}" { return CLOSEB; }
"(" { return OPENP; }
")" { return CLOSEP; }
";" { return SECO; }
"printf" { return PRINT; }
"scanf" { return SCAN; }
"int" {return INT2;}
"main" {return MAIN; }
"true" {
    yylval.boolValue = strdup(yytext);
    return BOOL;
}
"false" {
    yylval.boolValue = strdup(yytext);
    return BOOL;
}
[a-z][a-zA-Z0-9]* {
    yylval.varName = strdup(yytext);
    return VAR;
}
.  { yyerror("unexpected character"); }
%%
