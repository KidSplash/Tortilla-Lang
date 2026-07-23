#include "AST.h"
#include <utility>

Node::Node(int l) {
    line = l;
}

PrgmNode::PrgmNode (int l, std::vector<std::unique_ptr<Node>> li) : Node(l) {
    list = std::move(li);
}
AssignNode::AssignNode (int l, DataType d, std::string n, Assigner a, std::unique_ptr<Node> v) : Node(l) {
    DT = d;
    name = std::move(n);
    asig = a;
    value = std::move(v);
}
BinOpNode::BinOpNode (int l, Val o, std::unique_ptr<Node> li, std::unique_ptr<Node> r, bool isOp, DataType d) : Node(l) {
    oper = std::move(o);
    exprLeft = std::move(li);
    exprRight = std::move(r);
    DT = d;
    isOpKey = isOp;
}
UnOpNode::UnOpNode (int l, Val o, std::unique_ptr<Node> e, bool isOp, DataType d) : Node(l) {
    isOpKey = isOp;
    oper = std::move(o);
    expr = std::move(e);
    DT = d;
}
BasicNode::BasicNode(int l, Kind t, std::string v, DataType d) : Node(l) {
    type = t;
    value = v;
    DT = d;
}
VarNode::VarNode (int l, std::string n, DataType d) : Node(l) {
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
