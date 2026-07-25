#ifndef TORTILLA_DEBUG_H
#define TORTILLA_DEBUG_H
#pragma once

#include <iostream>

#include "Common.h"
#include "AST.h"

inline void decodeToken(Token token) {
    std::cout << fromKind[token.kind];
    if (token.kind == Kind::Float || token.kind == Kind::Int
|| token.kind == Kind::Bool || token.kind == Kind::Var || token.kind == Kind::Str) {
        std::cout << ": " << std::get<std::string>(token.val);
}
    else if (token.kind == Kind::Keyword) {
        std::cout << ": " << fromKeywords[std::get<Keyword>(token.val)];
    }
    std::cout << "\n";
}
inline void decodeTokens(std::vector<Token> tokens) {
    int i = 0;
    while (i < tokens.size()) {
        decodeToken(tokens[i]);
        ++i;
    }
    std::cout << "\n\n";
}


inline void decodeNode(std::unique_ptr<Node> node);

inline void decodeAssign(AssignNode* node) {
    std::cout << "Var Assigned " << node->name << " (" << fromDataType[node->DT] << ", ";
    decodeNode(std::move(node->value));
    std::cout << ")\n";
}
inline void decodeUnOp(UnOpNode* node) {
    if (node->isOpKey == true) {
        std::cout << "(" << fromKeywords[std::get<Keyword>(node->oper)] << " ";
    }
    else {
        std::cout << "(" << fromOperator[std::get<Operator>(node->oper)] << " ";
    }
    decodeNode(std::move(node->expr));
    std::cout << ")";
}
inline void decodeBinOp(BinOpNode* node) {
    std::cout << "( ";
    decodeNode(std::move(node->exprLeft));
    std::cout << " " << fromOperator[std::get<Operator>(node->oper)] << " ";
    decodeNode(std::move(node->exprRight));
    std::cout << ")";
}
inline void decodeBasic(BasicNode* node) {
    std::cout << "Basic (" << fromKind[node->type] << ")";
}
inline void decodeVar(VarNode* node) {
    std::cout << "Var " << node->name << "(";
    std::cout << ")";
}

inline void decodeAST(PrgmNode node) {
    int i = 0;
    std::cout << "\n";
    while (i < node.list.size()) {
        decodeNode(std::move(node.list[i]));
        ++i;
    }
}
inline void decodeNode(std::unique_ptr<Node> node) {
    if (dynamic_cast<AssignNode*>(node.get())) {
        decodeAssign(static_cast<AssignNode*>(node.release()));
    }
    else if (dynamic_cast<BasicNode*>(node.get())) {
        decodeBasic(static_cast<BasicNode*>(node.release()));
    }
    else if (dynamic_cast<UnOpNode*>(node.get())) {
        decodeUnOp(static_cast<UnOpNode*>(node.release()));
    }
    else if (dynamic_cast<BinOpNode*>(node.get())) {
        decodeBinOp(static_cast<BinOpNode*>(node.release()));
    }
    else if (dynamic_cast<VarNode*>(node.get())) {
        decodeVar(static_cast<VarNode*>(node.release()));
    }
}

#endif