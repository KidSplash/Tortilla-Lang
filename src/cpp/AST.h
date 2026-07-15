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
    explicit BinOpNode(int l, Val o, std::unique_ptr<Node> li, std::unique_ptr<Node> r);
};
class UnOpNode : public Node {
public:
    Val oper;
    std::unique_ptr<Node> expr;
    explicit UnOpNode(int l, Val o, std::unique_ptr<Node> e);
};
class BasicNode : public Node {
public:
    Kind value;
    explicit BasicNode(int l, Kind v);
};
class VarNode : public Node {
public:
    std::string name;
    std::unique_ptr<Node> value;
    explicit VarNode(int l, std::string n);
};

#endif