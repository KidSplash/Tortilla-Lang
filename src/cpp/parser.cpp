#include "parser.h"
#include <iostream>

PrgmNode parse (const std::vector<Token>& code) {
    int i = 0;
    PrgmNode out(0, {});
    while (i < code.size()) {
        out.list.push_back(parseState(code, i));
    }
    return out;
}
std::unique_ptr<Node> parseState(const std::vector<Token>& code, int& i) {
    std::cout << "\n";
    if (code.at(i).kind == Kind::Keyword) {
        if (isDataType(std::get<Keyword>(code.at(i).val))) {
            return parseAssign(code, i);
        }
    }
    return pratt(code, i, 0);
}
std::unique_ptr<AssignNode> parseAssign(const std::vector<Token>& code, int& i) {
    std::cout << "Assign <" << fromKeywords[std::get<Keyword>(code.at(i).val)] << ">";
    int line = code.at(i).line;
    DataType DT = toDataType.at(std::get<Keyword>(code.at(i).val));
    std::string Name;
    Assigner Asig;
    std::unique_ptr<Node> val = nullptr;
    ++i; //past datatype
    std::cout << "[" << std::get<std::string>(code.at(i).val) << "] (";
    if (code.at(i).kind == Kind::Var) {
        Name = std::get<std::string>(code.at(i).val);
    }
    else {
        //error
        Name = "Error";
    }
    ++i; //pass var name
    if (code.at(i).kind == Kind::Assigner) {
        Asig = std::get<Assigner>(code.at(i).val);
        val = parseState(code, i);
    }
    else {
        Asig = Assigner::None;
    }
    std::cout << ")";
    return std::make_unique<AssignNode>(line, DT, Name, Asig, std::move(val));
}
std::unique_ptr<VarNode> parseVar(const std::vector<Token> &code, int& i) {
    std::cout << "Var [" << std::get<std::string>(code.at(i).val) << "]";
    int line = code.at(i).line;
    std::string name;
    if (auto* namePtr = std::get_if<std::string>(&code.at(i).val)) {
        name = *namePtr;
    }
    ++i; //pass var name
    if (i < code.size() && code.at(i).kind == Kind::Operator) {
        if (auto* ptr = std::get_if<Operator>(&code.at(i).val)) {
            if (*ptr == Operator::Then) {
                ++i;
                //return parseCall(code, i);
            }
        }
    }
    if (i >= code.size()) {
        return std::make_unique<VarNode>(line, name);
    }
    return std::make_unique<VarNode>(line, name);
}

std::unique_ptr<Node> pratt(const std::vector<Token> &code, int &i, const int minBP) {
    std::cout << "Pratt(";
    int lineNum = code.at(i).line;
    Val val = code.at(i).val;
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
    if (code.at(i).kind == Kind::Int || code.at(i).kind == Kind::Float || code.at(i).kind == Kind::Bool || code.at(i).kind == Kind::Str) {
        left = std::make_unique<BasicNode>(code.at(i).line, code.at(i).kind);
        std::cout << " num ";
        //pass num
        ++i;
    }
    else if (code.at(i).kind == Kind::Var) {
        left = parseVar(code, i);
    }
    else if (auto* opPtr = std::get_if<Operator>(&code.at(i).val)) {
        if (*opPtr == Operator::Minus || *opPtr == Operator::BitNot) {
            std::cout << " unOp ";
            ++i; // pass operator
            right = pratt(code, i, 90);
            left = std::make_unique<UnOpNode>(lineNum, val, std::move(right));
        }
    }
    else if (auto* keyPtr = std::get_if<Keyword>(&code.at(i).val)) {
        if (*keyPtr == Keyword::_not) {
            std::cout << " unOp ";
            ++i; //pass operator
            right = pratt(code, i, 90);
            left = std::make_unique<UnOpNode>(code.at(i).line, code.at(i).val, std::move(right));
        }
    }
    bool loopCheck = i < code.size();
    while (loopCheck == true) {
        if (BPChart.contains(code.at(i).val)) {
            int bp = BPChart.at(code.at(i).val);
            if (minBP <= bp) {
                std::cout << " (Y) ";
                ++i; //pass operator
                right = pratt(code, i, bp);
                if (i < code.size()) {
                    left = std::make_unique<BinOpNode>(code.at(i).line, code.at(i).val, std::move(left), std::move(right));
                }
                else {
                    left = std::move(right);
                }
                loopCheck = i < code.size();
            } else {
                std::cout << " (N) ";
                loopCheck = false;
            }
        } else {
            loopCheck = false;
        }
    }
    std::cout << ")";
    return left;
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