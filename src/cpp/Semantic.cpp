#include "Semantic.h"

Variable::Variable(DataType dt, bool hbd) {
    DT = dt;
    hasBeenDefined = hbd;
};

void hoister(PrgmNode node) {}   //Dont need this until add Functions

std::unordered_map<std::string, Variable> nameCheckAST(PrgmNode node) {
    int i = 0;
    std::unordered_map<std::string, Variable> vars {};
    while (i < node.list.size()) {
        nameCheckNode(std::move(node.list[i]), vars);
        ++i;
    }
    return vars;
}
void nameCheckNode(std::unique_ptr<Node> node, std::unordered_map<std::string, Variable>& vars) {
    if (dynamic_cast<AssignNode*>(node.get())) {
        nameCheckAssign(static_cast<AssignNode*>(node.release()), vars);
    }
    else if (dynamic_cast<UnOpNode*>(node.get())) {
        nameCheckUnOp(static_cast<UnOpNode*>(node.release()), vars);
    }
    else if (dynamic_cast<BinOpNode*>(node.get())) {
        nameCheckBinOp(static_cast<BinOpNode*>(node.release()), vars);
    }
    else if (dynamic_cast<VarNode*>(node.get())) {
        nameCheckVar(static_cast<VarNode*>(node.release()), vars);
    }
}
void nameCheckAssign(AssignNode* node, std::unordered_map<std::string, Variable>& vars) {
    if (vars.contains(node->name)) {
        //redefinition error
    }
    vars.insert({node->name, Variable(node->DT, true)});
}
void nameCheckUnOp(UnOpNode* node, std::unordered_map<std::string, Variable>& vars) {
    nameCheckNode(std::move(node->expr), vars);
}
void nameCheckBinOp(BinOpNode* node, std::unordered_map<std::string, Variable>& vars) {
    nameCheckNode(std::move(node->exprLeft), vars);
    nameCheckNode(std::move(node->exprRight), vars);
}
void nameCheckVar(VarNode* node, std::unordered_map<std::string, Variable>& vars) {
    if (!vars.contains(node->name)) {
        //error unefined variable
        vars.insert({node->name, Variable(DataType::None, true)});
    }
}