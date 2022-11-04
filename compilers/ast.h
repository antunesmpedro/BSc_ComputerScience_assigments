
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
    enum {
        E_INTEGER,
        E_VARIABLE,
        E_OPERATION,
        E_BOOL,
    } kind;
    union {
        int value; // for integer values
        char* name; // for variables
        char* bool1;// for bool
        struct {
            int operator; // PLUS, MINUS, etc
            struct _Expr* left;
            struct _Expr* right;
        } op; // for binary expressions
    } attr;
};

struct _Cmd {
    enum {
        E_IF,
        E_FOR,
        E_WHILE,
        E_ATR,
        E_PRINT,
        E_SCAN,
        E_DEBUG
    } kind;
    struct _Expr* expr1;
    struct _Expr* expr2;
    struct _Cmd* cmd1;
    struct _Cmd* cmd2;
};

struct _CmdList {
    struct _Cmd* cmd;
    struct _CmdList* next;
};


struct _ExprList {
    struct _Expr* expr;
    struct _ExprList* next;
};


typedef struct _Expr Expr;
typedef struct _ExprList ExprList;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;


// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_variable(char* a);
Expr* ast_bool(char* a);
Cmd* ast_if(Expr* expr, Cmd* cmd1, Cmd* cmd2);
Cmd* ast_if1(Expr* expr, Cmd*cmd1);
Cmd* ast_while(Expr* expr, Cmd* cmd1);
Cmd* ast_for1(Expr* expr, Cmd* cmd1);
Cmd* ast_for2(Expr* expr1, Expr* expr2, Expr* expr3, Cmd* cmd1);
Cmd* ast_atr(Expr* expr1, Expr* expr2);
Cmd* ast_print(Expr* expr);
Cmd* ast_scan(Expr* expr);
CmdList* ast_cmdlist(Cmd* cmd, CmdList* next);

#endif
