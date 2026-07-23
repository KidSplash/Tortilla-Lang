#include "Semantic.h"

Variable::Variable(DataType dt, bool hbd) {
    DT = dt;
    hasBeenDefined = hbd;
};

void hoister(PrgmNode node) {}   //Dont need this until add Functions

//Name Checker
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

//Type Checker
void typeCheckAST(PrgmNode node) {
    int i = 0;
    while (i < node.list.size()) {
        typeCheckNode(std::move(node.list[i]));
        ++i;
    }
}
DataType typeCheckNode(std::unique_ptr<Node> node) {
    if (dynamic_cast<AssignNode*>(node.get())) {
        typeCheckAssign(static_cast<AssignNode*>(node.release()));
    }
    else if (dynamic_cast<UnOpNode*>(node.get())) {
        return typeCheckUnOp(static_cast<UnOpNode*>(node.release()));
    }
    else if (dynamic_cast<BinOpNode*>(node.get())) {
        return typeCheckBinOp(static_cast<BinOpNode*>(node.release()));
    }
    else if (dynamic_cast<BasicNode*>(node.get())) {
        return typeCheckBasic(static_cast<BasicNode*>(node.release()));
    }
    return DataType::None;
}
void typeCheckAssign(AssignNode* node) {
    if (node->DT != typeCheckNode(std::move(node->value))) {
        //error: DataTypes do not align
    }
    else {

    }
}
DataType typeCheckUnOp(UnOpNode* node) {
    if (node->isOpKey == true) {
        Keyword oper = std::get<Keyword>(node->oper);
        if (oper == Keyword::_not) {
            return DataType::Bool;
        }
        return DataType::None;
    }
    DataType out = typeCheckNode(std::move(node->expr));
    if (out == DataType::Bigint || out == DataType::Int || out == DataType::Doub || out == DataType::Float) {
        return out;
    }
    //error
    return DataType::None;
}
DataType typeCheckBinOp(BinOpNode* node) {
    DataType left = typeCheckNode(std::move(node->exprLeft));
    DataType right = typeCheckNode(std::move(node->exprRight));
    if (node->isOpKey) {
        Keyword oper = std::get<Keyword>(node->oper);
    }
    Operator oper = std::get<Operator>(node->oper);
    if (oper == Operator::Divide) {
        if (left == DataType::Char || right == DataType::Char) {
            //error
            return DataType::None;
        }
        if (left == DataType::Doub || right == DataType::Doub || left == DataType::Bigint || right == DataType::Bigint) {
            return DataType::Doub;
        }
        return DataType::Float;
    }
    if (oper == Operator::Plus ||
        oper == Operator::Times ||
        oper == Operator::Minus ||
        oper == Operator::Power ||
        oper == Operator::BitAnd ||
        oper == Operator::BitOr ||
        oper == Operator::BitXor ||
        oper == Operator::Shl ||
        oper == Operator::Shr) {
        if (left == DataType::Char || right == DataType::Char) {
            if (oper == Operator::Plus) {
                return DataType::Char; //TODO: Change to a string once strings are added
                //TODO: Make a function to check if the left and right values are valid numbers and if so, DT = num, else DT = ???
            }
            return DataType::None;
        }
        if (left == DataType::Doub || right == DataType::Doub) {
            return DataType::Doub;
        }
        if (left == DataType::Float || right == DataType::Float) {
            if (left == DataType::Bigint || right == DataType::Bigint) {
                return DataType::Doub;
            }
            return DataType::Float;
        }
        if (left == DataType::Bigint || right == DataType::Bigint) {
            return DataType::Bigint;
        }
        if (left == DataType::Int || right == DataType::Int) {
            return DataType::Int;
        }
        if (left == DataType::Bool || right == DataType::Bool) {
            return DataType::Int;
        }
    }

    return DataType::None;

}
DataType typeCheckBasic(BasicNode* node) {
    return kindToDataType[node->type];
}