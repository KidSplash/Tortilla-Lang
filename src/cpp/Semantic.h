#ifndef TORTILLA_SEMANTIC_H
#define TORTILLA_SEMANTIC_H
#pragma once

#include "Common.h"
#include "AST.h"

AST nameCheckPrgm(PrgmNode prgm, std::unordered_map<std::string, Variable>& globalVars);
int nameCheckNode(Node &self, std::unordered_map<std::string, Variable>& globalVars);
int nameCheckAssign(Node &self, std::unordered_map<std::string, Variable>& globalVars);
int nameCheckBinOp(Node &self, std::unordered_map<std::string, Variable>& globalVars);
int nameCheckUnOp(Node &self, std::unordered_map<std::string, Variable>& globalVars);
int nameCheckVar(Node &self, std::unordered_map<std::string, Variable>& globalVars);

/*void hoister(PrgmNode node);   //Dont need this till add Functions*/

void typeCheckPrgm(PrgmNode& prgm, std::unordered_map<std::string, Variable>& globalVars);
typeChecked typeCheckNode(Node& self, std::unordered_map<std::string, Variable>& globalVars);
typeChecked typeCheckAssign(Node& self, std::unordered_map<std::string, Variable>& globalVars);
typeChecked typeCheckBinOp(Node& self, std::unordered_map<std::string, Variable>& globalVars);
typeChecked typeCheckUnOp(Node& self, std::unordered_map<std::string, Variable>& globalVars);
typeChecked typeCheckVar(Node& self, std::unordered_map<std::string, Variable>& globalVars);
typeChecked typeCheckBasic(Node& self, std::unordered_map<std::string, Variable>& globalVars);

#endif