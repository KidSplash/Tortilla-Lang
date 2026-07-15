#ifndef TORTILLA_PARSER_H
#define TORTILLA_PARSER_H
#pragma once

#include "Common.h"
#include "AST.h"
#include <vector>


PrgmNode parse(const std::vector<Token>& code);
std::unique_ptr<Node> parseState(const std::vector<Token>& code, int& i);
std::unique_ptr<AssignNode> parseAssign(const std::vector<Token>& code, int& i);
std::unique_ptr<VarNode> parseVar(const std::vector<Token>& code, int& i);
std::unique_ptr<Node> pratt(const std::vector<Token>& code, int& i, int minBP);
/*
State > (Assign, Expr)

Assign > DT + Name + <Expr>
Expr > (BinOp, UnOp, Var, Group, Literal)
BinOp > Expr + (binary op) + Expr
UnOp > (unary op) + Expr
Name >|
Group > Lister + Expr + Lister
Literal >|
Lister >|   // [], {}, ()

*/

#endif