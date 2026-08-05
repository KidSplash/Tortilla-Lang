#include "AST.h"
#include <utility>

PrgmNode::PrgmNode (int l, int c, std::vector<std::unique_ptr<Node>> li, std::vector<Variable> v) {
    line = l;
    column = c;
    list = std::move(li);
    variables = v;
}
Node::Node (int l, int c, nodeType t, DataType dt1, DataType dt2,
    std::string n, std::unique_ptr<Node> n1, std::unique_ptr<Node> n2, bool s, Assigner a, Val o) {
    line = l;
    column = c;
    type = t;
    DT1 = dt1;
    DT2 = dt2;
    text = n;
    asig = a;
    oper = o;
    node1 = std::move(n1);
    node2 = std::move(n2);
    spec = s;
}
