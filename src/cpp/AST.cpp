#include "AST.h"
#include <utility>

Node::Node(int l, int c) {
    line = l;
    column = c;
}

PrgmNode::PrgmNode (int l, int c, std::vector<std::unique_ptr<Node>> li) : Node(l, c) {
    list = std::move(li);
}
AssignNode::AssignNode (int l, int c,  DataType d, std::string n, Assigner a, std::unique_ptr<Node> v) : Node(l, c) {
    DT = d;
    name = std::move(n);
    asig = a;
    value = std::move(v);
}
BinOpNode::BinOpNode (int l, int c, Val o, std::unique_ptr<Node> li, std::unique_ptr<Node> r, bool isOp, DataType d) : Node(l, c) {
    oper = std::move(o);
    exprLeft = std::move(li);
    exprRight = std::move(r);
    DT = d;
    isOpKey = isOp;
}
UnOpNode::UnOpNode (int l, int c, Val o, std::unique_ptr<Node> e, bool isOp, DataType d) : Node(l, c) {
    isOpKey = isOp;
    oper = std::move(o);
    expr = std::move(e);
    DT = d;
}
BasicNode::BasicNode(int l, int c, Kind t, std::string v, DataType d) : Node(l, c) {
    type = t;
    value = v;
    DT = d;
}
VarNode::VarNode (int l, int c, std::string n, DataType d) : Node(l, c) {
    name = std::move(n);
    DT = d;
}
/*
State > (Assign, Expr)

Assign > DT + Name + <Expr>
Expr > (BinOp, UnOp, Var, Group, Literal)
BinOp > Expr + (binary op) + Expr
UnOp > (unary op) + Expr
Name >|
Group > Lister + Expr + Lister
Literal >|
Lister >|   // [], {}, ()

*/
