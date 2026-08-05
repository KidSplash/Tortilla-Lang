#ifndef TORTILLA_AST_H
#define TORTILLA_AST_H
#pragma once

#include "Common.h"
#include <vector>
#include <variant>
#include <memory>

enum class nodeType {
    Assign,
    BinOp,
    UnOp,
    Basic,
    Var,
    None,
};

class Node;

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
    std::unique_ptr<Node> node1;//value, left, Expr, ---,
    std::unique_ptr<Node> node2;//---, right, ---, ---,
    bool spec;//isDeclaration, isOpKey, isOpKey, ---,
    Assigner asig;
    Val oper;
    explicit Node(int l=0, int c=0, nodeType t=nodeType::None,
        DataType dt1=DataType::None, DataType dt2=DataType::None, std::string n="",
        std::unique_ptr<Node> n1=nullptr, std::unique_ptr<Node> n2=nullptr, bool s=false, Assigner a=Assigner::None, Val o={});
};
class PrgmNode {
public:
    int line;
    int column;
    std::vector<std::unique_ptr<Node>> list;
    std::vector<Variable> variables;
    explicit PrgmNode(int l, int c, std::vector<std::unique_ptr<Node>> li, std::vector<Variable> v);
};
struct AST {
    PrgmNode prgm;
    std::unordered_map<std::string, Variable> globals;
};
struct typeChecked {
    DataType DT;
    bool valid;
    std::string value;
};
#endif