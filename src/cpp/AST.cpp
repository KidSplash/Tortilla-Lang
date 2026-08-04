#include "AST.h"
#include <utility>

PrgmNode::PrgmNode (int l, int c, std::vector<node> li, std::vector<Variable> v) {
    line = l;
    column = c;
    list = std::move(li);
    variables = v;
}
Node::Node (int l, int c, nodeType t, DataType dt1, DataType dt2,
    std::string n, node n1, node n2, bool s, Assigner a, Val o) {
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
