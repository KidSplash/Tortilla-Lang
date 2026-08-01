#ifndef TORTILLA_SEMANTIC_H
#define TORTILLA_SEMANTIC_H
#pragma once

#include "Common.h"
#include "AST.h"

void hoister(PrgmNode node);   //Dont need this till add Functions

AST nameCheckAST(PrgmNode node);
int nameCheckNode(std::unique_ptr<Node> node, std::unordered_map<std::string, Variable>& vars);
int nameCheckAssign(AssignNode* node, std::unordered_map<std::string, Variable>& vars);
void nameCheckUnOp(UnOpNode* node, std::unordered_map<std::string, Variable>& vars);
void nameCheckBinOp(BinOpNode* node, std::unordered_map<std::string, Variable>& vars);
int nameCheckVar(VarNode* node, std::unordered_map<std::string, Variable>& vars);

AST typeCheckAST(PrgmNode node);
DataType typeCheckNode(std::unique_ptr<Node> node);
void typeCheckAssign(AssignNode* node);
DataType typeCheckUnOp(UnOpNode* node);
DataType typeCheckBinOp(BinOpNode* node);
DataType typeCheckBasic(BasicNode* node);

#endif