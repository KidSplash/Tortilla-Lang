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
    Node(int l);
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
    explicit PrgmNode(int l, std::vector<std::unique_ptr<Node>> li);
};
class AssignNode : public Node {
public:
    DataType DT;
    std::string name;
    Assigner asig;
    std::unique_ptr<Node> value;
    explicit AssignNode(int l, DataType d, std::string n, Assigner a, std::unique_ptr<Node> v);
};
class BinOpNode : public Node {
public:
    Val oper;
    std::unique_ptr<Node> exprLeft;
    std::unique_ptr<Node> exprRight;
    bool isOpKey;
    DataType DT;
    explicit BinOpNode(int l, Val o, std::unique_ptr<Node> li, std::unique_ptr<Node> r, bool isOp, DataType dt);
};
class UnOpNode : public Node {
public:
    Val oper;
    std::unique_ptr<Node> expr;
    bool isOpKey;
    DataType DT;
    explicit UnOpNode(int l, Val o, std::unique_ptr<Node> e, bool isOp, DataType dt);
};
class BasicNode : public Node {
public:
    Kind type;
    std::string value;
    DataType DT;
    explicit BasicNode(int l, Kind t, std::string v, DataType dt);
};
class VarNode : public Node {
public:
    std::string name;
    DataType DT;
    explicit VarNode(int l, std::string n, DataType dt);
};

#endif