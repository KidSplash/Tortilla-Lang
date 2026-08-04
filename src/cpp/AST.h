#ifndef TORTILLA_AST_H
#define TORTILLA_AST_H
#pragma once

#include "Common.h"
#include <vector>
#include <variant>
#include <memory>

enum class nodeType {
    Prgm,
    Assign,
    BinOp,
    UnOp,
    Basic,
    Var,
    None,
};

class Node;

using AnyOp = std::variant<std::monostate, Operator, Keyword>;
using node = std::variant<std::unique_ptr<Node>, std::monostate>;
/*
Assign (needs: Assigned DT, Expression DT, Name, IsDefinition, value, assigner)
BinOp (needs: DataType 1 and 2, value 1 and 2, operator, isOpKey)
UnOp (needs: DataType, value, operator, isOpKey)
Var (needs: Name)
Basic (needs: Value, DataType)
List (needs: list of Nodes, list of Variables)
*/
class Node {
public: //Assign, BinOp, UnOp, Basic
    //Var = only name
    int line;
    int column;
    nodeType type;
    DataType DT1;//Assigned, left, Expr, DT,
    DataType DT2;//Expr, right, ---, ---,
    std::string text;//Name, ---, ---, value,
    Assigner asig;
    AnyOp oper;
    node node1;//value, left, Expr, ---,
    node node2;//---, right, ---, ---,
    bool specifier;//isDeclaration, isOpKey, isOpKey, ---,
    explicit Node(int l=0, int c=0, nodeType t=nodeType::None,
        DataType dt1=DataType::None, DataType dt2=DataType::None, std::string n="",
        node n1={}, node n2={}, bool s=false, Assigner a=Assigner::None, AnyOp o={});
};

class PrgmNode {
public:
    int line;
    int column;
    nodeType type;
    std::vector<node> list;
    std::vector<Variable> variables;
    explicit PrgmNode(int l, int c, nodeType t, std::vector<node> li, std::vector<Variable> v);
};

struct AST {
    std::unordered_map<std::string, Variable> vars;
    PrgmNode ast;
};

#endif