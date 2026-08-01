#ifndef TORTILLA_AST_H
#define TORTILLA_AST_H
#pragma once

#include "Common.h"
#include <vector>
#include <memory>


class Node {
public:
    virtual ~Node() = default;
    int line;
    int column;
    Node(int l, int c);
};
class PrgmNode;
class AssignNode;
class BinOpNode;
class UnOpNode;
class BasicNode;
class VarNode;

using expression = std::variant<std::string, Node>;

class PrgmNode : public Node {
public:
    std::vector<std::unique_ptr<Node>> list;
    explicit PrgmNode(int l, int c, std::vector<std::unique_ptr<Node>> li);
};
class AssignNode : public Node {
public:
    DataType DT;
    std::string name;
    Assigner asig;
    std::unique_ptr<Node> value;
    bool declaration;
    explicit AssignNode(int l, int c, DataType d, std::string n, Assigner a, std::unique_ptr<Node> v, bool dec);
};
class BinOpNode : public Node {
public:
    Val oper;
    std::unique_ptr<Node> exprLeft;
    std::unique_ptr<Node> exprRight;
    bool isOpKey;
    DataType DT;
    explicit BinOpNode(int l, int c, Val o, std::unique_ptr<Node> li, std::unique_ptr<Node> r, bool isOp, DataType dt);
};
class UnOpNode : public Node {
public:
    Val oper;
    std::unique_ptr<Node> expr;
    bool isOpKey;
    DataType DT;
    explicit UnOpNode(int l, int c, Val o, std::unique_ptr<Node> e, bool isOp, DataType dt);
};
class BasicNode : public Node {
public:
    Kind type;
    std::string value;
    DataType DT;
    explicit BasicNode(int l, int c, Kind t, std::string v, DataType dt);
};
class VarNode : public Node {
public:
    std::string name;
    DataType DT;
    explicit VarNode(int l, int c, std::string n, DataType dt);
};

struct AST {
    std::unordered_map<std::string, Variable> vars;
    PrgmNode ast;
};

#endif