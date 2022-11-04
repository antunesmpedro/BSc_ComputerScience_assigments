#include <stdio.h>
#include "parser.h"

void printcmd(Cmd* cmd);
void printexpr(Expr* expr);
void printcmdlist(CmdList* cmdlist);

void printexpr(Expr* expr) {
    if (expr == 0) {
        yyerror("Null expression!!");
    }
    else if (expr->kind == E_INTEGER) {
        printf("Integer: %d\n", expr->attr.value);
    }
    else if (expr->kind == E_VARIABLE) {
        printf("Variable: %s\n", expr->attr.name);
    }
    else if (expr->kind == E_OPERATION) {
        switch (expr->attr.op.operator) {
            case PLUS:
            printf("Operator: +\n");
            break;
            case MINUS:
            printf("Operator: -\n");
            break;
            case TIMES:
            printf("Operator: *\n");
            break;
            case DIV:
            printf("Operator: /\n");
            break;
            case GREAT:
            printf("Operator: >\n");
            break;
            case LESS:
            printf("Operator: <\n");
            break;
            case GREATEQ:
            printf("Operator: >=\n");
            break;
            case LESSEQ:
            printf("Operator: <=\n");
            break;
            case EQUALS:
            printf("Operator: ==\n");
            break;
            case DIFF:
            printf("Operator: !=\n");
            break;
            case ATR:
            printf("Operator: =\n");
            break;
            // TODO Other cases here ...
            default: yyerror("Unknown operator!");
        }
        if (expr->attr.op.left->kind == E_INTEGER) {
            printf("Constant: %d\n", expr->attr.op.left->attr.value);
        }
        else if (expr->attr.op.left->kind == E_VARIABLE) {
            printf("Variable: %s\n", expr->attr.op.left->attr.name);
        }
        else {
            printf("Boolean: %s\n", expr->attr.op.left->attr.bool1);
        }

        if (expr->attr.op.right->kind == E_INTEGER) {
            printf("Constant: %d\n", expr->attr.op.right->attr.value);
        }
        else if (expr->attr.op.right->kind == E_VARIABLE) {
            printf("Variable: %s\n", expr->attr.op.right->attr.name);
        }
        else {
            printf("Boolean: %s\n", expr->attr.op.right->attr.bool1);
        }
    }
}

void printcmdlist(CmdList* cmdlist) {
    printcmd(cmdlist->cmd);
    printf("\n");
    if (cmdlist->next != NULL) {
        printcmdlist(cmdlist->next);
    }
}



void printcmd(Cmd* cmd) {
    if (cmd == 0) {
        yyerror("Null command!!");
    }
    else if (cmd->kind == E_DEBUG) {
        printexpr(cmd->expr1);
        printf("%d\n", cmd->expr1->attr.op.right->attr.value);
    }
    else if (cmd->kind == E_IF) {
        printf("Command: If\n");
        printf("Condition:");
        printexpr(cmd->expr1);
        if (cmd->expr1->attr.op.left == NULL) {
            printf("null\n");
        }
         printf("- Then -\n");
        printcmd(cmd->cmd1);
        printf("- Else -\n");
        printcmd(cmd->cmd2);
    }
    else if (cmd->kind == E_WHILE) {
        printf("Command: While\n");
        printf("Condition:");
        printexpr(cmd->expr1);
        if (cmd->expr1->attr.op.left == NULL) {
            printf("null\n");
        }
        printcmd(cmd->cmd1);
    }
    else if (cmd->kind == E_ATR) {
        printf("Command: =\n");
        printexpr(cmd->expr1);
        printexpr(cmd->expr2);
    }
    else if (cmd->kind == E_FOR) {
        printf("Command: For\n");
        printf("Condition: ");
        printexpr(cmd->expr1);
        printcmd(cmd->cmd1);
    }
    else if (cmd->kind == E_SCAN) {
        printf("Command: Scan\n");
        printexpr(cmd->expr1);
    }
    else if (cmd->kind == E_PRINT) {
        printf("Command: Print\n");
        printexpr(cmd->expr1);
    }
}

int main(int argc, char** argv) {
    --argc; ++argv;
    if (argc != 0) {
        yyin = fopen(*argv, "r");
        if (!yyin) {
            printf("'%s': could not open file\n", *argv);
            return 1;
        }
    } //  yyin = stdin
    if (yyparse() == 0) {
        //printf("Result = %d\n", eval(root));
        printcmdlist(root);
    }
    return 0;


}
