// Tokens
%token
INT
VAR
PLUS
MINUS
TIMES
DIV
EQUALS
DIFF
GREAT
LESS
GREATEQ
LESSEQ
IF
ELSE
WHILE
FOR
OPENB
CLOSEB
OPENP
CLOSEP
BOOL
ATR
SECO
SCAN
PRINT
INT2 
MAIN

// Operator associativity & precedence
%left PLUS
%left MINUS
%left TIMES
%left DIV
%left EQUALS
%left DIFF
%left GREAT
%left LESS
%left GREATEQ
%left LESSEQ
%right ATR

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
    int intValue;
    char* varName;
    char* boolValue;
    Expr* exprValue;
    Cmd* cmdValue;
    CmdList* cmdList;
}

%type <intValue> INT
%type <varName> VAR
%type <boolValue> BOOL
%type <exprValue> expr
%type <cmdValue> cmd
%type <cmdList> cmd_list


// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"

    extern int yylex();
    extern int yyline;
    extern char* yytext;
    extern FILE* yyin;
    extern void yyerror(const char* msg);
    CmdList* root;
}

%%
program: INT2 MAIN OPENP CLOSEP OPENB cmd_list CLOSEB { root = $6; }

expr:
    INT {
        $$ = ast_integer($1);
    }
    |
    VAR {
        $$ = ast_variable($1);
    }
    |
    BOOL {
        $$ = ast_bool($1);
    }
    |
    expr PLUS expr {
        $$ = ast_operation(PLUS, $1, $3);
    }
    |
    expr MINUS expr {
        $$ = ast_operation(MINUS, $1, $3);
    }
    |
    expr TIMES expr {
        $$ = ast_operation(TIMES, $1, $3);
    }
    |
    expr DIV expr {
        $$ = ast_operation(DIV, $1, $3);
    }
    |
    expr EQUALS expr {
        $$ = ast_operation(EQUALS, $1, $3);
    }
    |
    expr DIFF expr {
        $$ = ast_operation(DIFF, $1, $3);
    }
    |
    expr GREAT expr {
        $$ = ast_operation(GREAT, $1, $3);
    }
    |
    expr LESS expr {
        $$ = ast_operation(LESS, $1, $3);
    }
    |
    expr GREATEQ expr {
        $$ = ast_operation(GREATEQ, $1, $3);
    }
    |
    expr LESSEQ expr {
        $$ = ast_operation(LESSEQ, $1, $3);
    }
    ;

cmd:
    IF OPENP expr CLOSEP OPENB cmd CLOSEB {
        $$ = ast_if1($3, $6);
    }
    |
    IF OPENP expr CLOSEP OPENB cmd CLOSEB ELSE OPENB cmd CLOSEB {
        $$ = ast_if($3, $6, $10);
    }
    |
    WHILE OPENP expr CLOSEP OPENB cmd CLOSEB {
        $$ = ast_while($3, $6);
    }
    |
    FOR expr OPENB cmd CLOSEB {
        $$ = ast_for1($2, $4);
    }
    |
    FOR OPENP VAR ATR expr SECO expr SECO VAR ATR expr CLOSEP OPENB cmd CLOSEB {
        $$ = ast_for2($5, $7, $11, $14);
    }
    |
    expr ATR expr SECO{
        $$ = ast_atr($1, $3);
    }
    |
    PRINT OPENP expr CLOSEP SECO{
        $$ = ast_print($3);
    }
    |
    SCAN OPENP expr CLOSEP SECO {
        $$ = ast_scan($3);
    }
    ;

cmd_list:
    cmd {
        $$ = ast_cmdlist($1, NULL);
    }
    |
    cmd cmd_list {
        $$ = ast_cmdlist($1, $2);
    }
    ;



%%

void yyerror(const char* err) {
printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
