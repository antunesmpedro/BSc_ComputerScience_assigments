// AST constructor functions

#include <stdlib.h> // for malloc
#include <stdio.h>
#include <string.h>
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr* ast_variable(char* a) {
    Expr* node = (Expr*) malloc(sizeof(Expr));
    node->kind = E_VARIABLE;
    node->attr.name = strdup(a);
    return node;
}

Expr* ast_bool(char* a) {
    Expr* node = (Expr*) malloc(sizeof(Expr));
    node->kind = E_BOOL;
    node->attr.bool1 = strdup(a);
    return node;
}

Cmd* ast_if1(Expr* expr, Cmd* cmd1) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_IF;
    memcpy(&node->expr1, &expr, sizeof(Expr));
    memcpy(&node->cmd1, &cmd1, sizeof(Cmd));
    return node;
}

Cmd* ast_if(Expr* expr, Cmd* cmd1, Cmd* cmd2) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_IF;
    node->expr1 = expr;
    node->cmd1 = cmd1;
    node->cmd2 = cmd2;
    return node;
}

Cmd* ast_while(Expr* expr, Cmd* cmd1) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_WHILE;
    node->expr1 = expr;
    node->cmd1 = cmd1;
    return node;
}

Cmd* ast_for1(Expr* expr, Cmd* cmd1) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_FOR;
    node->expr1 = expr;
    node->cmd1 = cmd1;
    return node;
}

Cmd* ast_for2(Expr* expr1, Expr* expr2, Expr* expr3, Cmd* cmd1) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_FOR;
    node->expr1 = expr1;
    node->cmd1 = cmd1;
    return node;
}

Cmd* ast_atr(Expr* expr1, Expr* expr2) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_ATR;
    memcpy(&node->expr1, &expr1, sizeof(Expr));
    memcpy(&node->expr2, &expr2, sizeof(Expr));
    return node;
}

Cmd* ast_print(Expr* expr) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_PRINT;
    memcpy(&node->expr1, &expr, sizeof(Expr));
    return node;
}

Cmd* ast_scan(Expr* expr) {
    Cmd* node = (Cmd*) malloc(sizeof(Cmd));
    node->kind = E_SCAN;
    memcpy(&node->expr1, &expr, sizeof(Expr));
    return node;
}

CmdList* ast_cmdlist(Cmd* cmd, CmdList* next) {
    CmdList* node = (CmdList*) malloc(sizeof(CmdList));
    node->cmd = cmd;
    memcpy(&node->next, &next, sizeof(CmdList));
    return node;
}
