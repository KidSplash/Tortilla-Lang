#ifndef TORTILLA_SEMANTIC_H
#define TORTILLA_SEMANTIC_H
#pragma once

#include "Common.h"
#include "AST.h"

class Variable {
public:
    DataType DT;
    bool hasBeenDefined;
    Variable(DataType dt, bool hbd);
};

void hoister(PrgmNode node);   //Dont need this till add Functions

std::unordered_map<std::string, Variable> nameCheckAST(PrgmNode node);
void nameCheckNode(std::unique_ptr<Node> node, std::unordered_map<std::string, Variable>& vars);
void nameCheckAssign(AssignNode* node, std::unordered_map<std::string, Variable>& vars);
void nameCheckUnOp(UnOpNode* node, std::unordered_map<std::string, Variable>& vars);
void nameCheckBinOp(BinOpNode* node, std::unordered_map<std::string, Variable>& vars);
void nameCheckVar(VarNode* node, std::unordered_map<std::string, Variable>& vars);

#endif