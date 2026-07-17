#ifndef TORTILLA_DEBUG_H
#define TORTILLA_DEBUG_H
#pragma once

#include <iostream>

#include "Common.h"
#include "AST.h"

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
    std::cout << "Basic (" << fromKind[node->value] << ")";
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