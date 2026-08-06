#include "Semantic.h"
#include "error.h"

Variable::Variable(DataType dt, bool hbd) {
    DT = dt;
    hasBeenDefined = hbd;
}

AST nameCheckPrgm(PrgmNode prgm, std::unordered_map<std::string, Variable>& globalVars) {
    int i = 0;
    std::unordered_map<std::string, Variable> vars {};
    while (i < prgm.list.size()) {
        if (nameCheckNode(*prgm.list[i], globalVars) != 0) {
            prgm.list.erase(prgm.list.begin() + i);
            --i;
        }
        ++i;
    }
    return {std::move(prgm), globalVars};
}
int nameCheckNode(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    switch (self.type) {
        case(nodeType::Assign):
            return nameCheckAssign(self, globalVars);
        case(nodeType::Var):
            return nameCheckVar(self, globalVars);
        case(nodeType::BinOp):
            return nameCheckBinOp(self, globalVars);
        case(nodeType::UnOp):
            return nameCheckUnOp(self, globalVars);
        default:
            return 0;
    }
}
int nameCheckAssign(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    int out = 0;
    if (globalVars.contains(self.text)) {
        if (self.spec == true) {
            errorAdd(error::N01, Pass::NameCheck, self.line, self.column);
            return 1;
        }
        out = nameCheckNode(*self.node1, globalVars);
        return out;
    }
    out = nameCheckNode(*self.node1, globalVars);
    globalVars.insert({self.text, Variable(self.DT1, true)});
    return out;
}
int nameCheckBinOp(Node &self, std::unordered_map<std::string, Variable>& globalVars) {
    int out = 0;
    out = nameCheckNode(*self.node1, globalVars);
    out += nameCheckNode(*self.node2, globalVars);
    return out;
}
int nameCheckUnOp(Node &self, std::unordered_map<std::string, Variable>& globalVars) {
    return nameCheckNode(*self.node1, globalVars);
}
int nameCheckVar(Node &self, std::unordered_map<std::string, Variable>& globalVars) {
    if (!globalVars.contains(self.text)) {
        errorAdd(error::N02, Pass::NameCheck, self.line, self.column);
        globalVars.insert({self.text, Variable(DataType::None, true)});
    }
    return 0;
}

/*
void hoister(PrgmNode node) {}   //Dont need this until add Functions

//Name Checker
AST nameCheckAST(PrgmNode node) {
    int i = 0;
    std::unordered_map<std::string, Variable> vars {};
    while (i < node.list.size()) {
        int legal = nameCheckNode(std::move(node.list[i]), vars);
        if (legal > 0) {
            node.list.erase(node.list.begin() + i);
        }
        ++i;
    }
    return {vars, std::move(node)};
}*/
/*
expr = anything
num = int, float, bigint, doub
col = str, array, dict, set

not: expr > bool
!: num > num

<, >, <=, >=, is, and, or, xor, nor: expr > bool
+: num > num; col > col; char/str > str
num:
/:num > float/doub
**, *, %, -, >>, <<, |, &, ^: num > num



in: expr-col > bool
has: col-expr > bool
+=, -=, *=, /=, %=, =: var-expr > none
++, –: var- > none
*/
/*
Type Checker:
int Assign(Node, vars):
check value = DataType
*/

DataType checkNum(DataType left, DataType right) {
    if (right == DataType::Char or right == DataType::None or right == DataType::Bool or left == DataType::Char or left == DataType::None or left == DataType::Bool) {
        return DataType::None;
    }
    if (left == DataType::Doub or right == DataType::Doub) {
        return DataType::Doub;
    }
    if (left == DataType::Float or right == DataType::Float) {
        if (left == DataType::Bigint or right == DataType::Bigint) {
            return DataType::Doub;
        }
        return DataType::Float;
    }
    if (left == DataType::Bigint or right == DataType::Bigint) {
        return DataType::Bigint;
    }
    if (left == DataType::Int and right == DataType::Int) {
        return DataType::Int;
    }
    return DataType::None;
}

void typeCheckPrgm(PrgmNode& prgm, std::unordered_map<std::string, Variable>& globalVars) {
    int i = 0;
    while (i < prgm.list.size()) {
        if (typeCheckNode(*prgm.list[i], globalVars).valid == false) {
            prgm.list.erase(prgm.list.begin() + i);
            --i;
        }
        ++i;
    }
}
typeChecked typeCheckNode(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    switch (self.type) {
        case(nodeType::Assign):
            return typeCheckAssign(self, globalVars);
        case(nodeType::Var):
            return typeCheckVar(self, globalVars);
        case(nodeType::Basic):
            return typeCheckVar(self, globalVars);
        case(nodeType::BinOp):
            return typeCheckBinOp(self, globalVars);
        case(nodeType::UnOp):
            return typeCheckUnOp(self, globalVars);
        default:
            return {DataType::None, false};
    }
}
typeChecked typeCheckAssign(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    typeChecked value = typeCheckNode(*self.node1, globalVars);
    if (self.DT1 == value.DT) {

    }
    return {DataType::None, false, ""};
}
typeChecked typeCheckBinOp(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    typeChecked left = typeCheckNode(*self.node1, globalVars);
    typeChecked right = typeCheckNode(*self.node2, globalVars);
    if (left.valid == false or right.valid == false) {
        return {DataType::None, false, ""};
    }
    if (self.spec == true) {
        Keyword oper = std::get<Keyword>(self.oper);
        if (oper == Keyword::_and or oper == Keyword::_or or oper == Keyword::_xor or oper == Keyword::_nor) {
            if (left.DT == DataType::Bool and right.DT == DataType::Bool) {
                return {DataType::Bool, true, ""};
            }
            //wrong DT
        }
        else if (oper == Keyword::_is) {
            return {DataType::Bool, true, ""};
        }
    }
    else {
        Operator oper = std::get<Operator>(self.oper);
        if (oper == Operator::Gte or oper == Operator::Lte or oper == Operator::Less or oper == Operator::More) {
            if (checkNum(left.DT, right.DT) != DataType::None) {
                return {DataType::Bool, true, ""};
            }
        }
        else if (oper == Operator::Divide) {
            if (checkNum(left.DT, right.DT) != DataType::None) {
                if (left.DT == DataType::Bigint or right.DT == DataType::Bigint or left.DT == DataType::Doub or right.DT == DataType::Doub) {
                    return {DataType::Doub, true, ""};
                }
                return {DataType::Float, true, ""};
            }
        }
        else if (oper == Operator::Plus) {
            if (left.DT == DataType::Char or right.DT == DataType::Char) {
                return {DataType::Char, true, ""};  //TODO: Update when strings are added
            }
            DataType out = checkNum(left.DT, right.DT);
            if (out != DataType::None) {
                return {out, true, ""};
            }
        }
        else {
            DataType out = checkNum(left.DT, right.DT);
            if (out != DataType::None) {
                return {out, true, ""};
            }
        }
    }
    //Wrong DataType Error
    return {DataType::None, false, ""};
}
typeChecked typeCheckUnOp(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    typeChecked value = typeCheckNode(*self.node1, globalVars);
    if (value.valid == false) {
        return {DataType::None, false, ""};
    }
    if (self.spec == true) {
        Keyword oper = std::get<Keyword>(self.oper);
        if (oper == Keyword::_not) {
            if (value.DT == DataType::Bool) {
                return {DataType::Bool, true, ""};
            }
            //wrong DT
        }
    }
    else {
        Operator oper = std::get<Operator>(self.oper);
        if (oper == Operator::BitNot or oper == Operator::Minus) {
            if (value.DT == DataType::Int or value.DT == DataType::Bigint or value.DT == DataType::Float or value.DT == DataType::Doub) {
                return {value.DT, true, ""};
            }
            //wrong DT
        }
    }
    return {DataType::None, false, ""};
}
typeChecked typeCheckVar(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    if (globalVars.contains(self.text)) {
        return {globalVars.at(self.text).DT, true, ""};
    }
    return {DataType::None, false, self.text};
}
typeChecked typeCheckBasic(Node& self, std::unordered_map<std::string, Variable>& globalVars) {
    return {self.DT1, true, self.text};
}


//Type Checker
/*AST typeCheckAST(AST ast) {
    int i = 0;
    AST newAst = {ast.vars, ast.ast};
    while (i < ast.ast.list.size()) {
        newAst = typeCheckNode(std::move(ast.ast.list[i]));
        ++i;
    }
    return ast;
}





AST typeCheckAST(AST ast) {
    int i = 0;
    AST newAst = {ast.vars, ast.ast};
    while (i < ast.ast.list.size()) {
        newAst = typeCheckNode(std::move(ast.ast.list[i]));
        ++i;
    }
    return ast;
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
        switch (node->DT) {
            case(DataType::Bigint):
                if (typeCheckNode(std::move(node->value)) != DataType::Int) {
                    node->DT = typeCheckNode(std::move(node->value));
                }
                break;
            case(DataType::Doub):
                if (typeCheckNode(std::move(node->value)) == DataType::Bigint || typeCheckNode(std::move(node->value)) == DataType::Float) {
                    break;
                }
            case(DataType::Float):
                if (typeCheckNode(std::move(node->value)) == DataType::Int) {
                    break;
                }
            default:
                node->DT = typeCheckNode(std::move(node->value));
        }
        errorAdd(error::T01, Pass::TypeCheck, node->line, node->column);
    }
}
DataType typeCheckUnOp(UnOpNode* node) {
    if (node->isOpKey == true) {
        Keyword oper = std::get<Keyword>(node->oper);
        if (oper == Keyword::_not) {
            return DataType::Bool;
        }
        errorAdd(error::A00, Pass::TypeCheck, node->line, node->column);
        return DataType::None;
    }
    DataType out = typeCheckNode(std::move(node->expr));
    if (out == DataType::Bigint || out == DataType::Int || out == DataType::Doub || out == DataType::Float) {
        return out;
    }
    errorAdd(error::T02, Pass::TypeCheck, node->line, node->column);
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
            errorAdd(error::T02, Pass::TypeCheck, node->line, node->column);
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
            errorAdd(error::T02, Pass::TypeCheck, node->line, node->column);
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
}*/