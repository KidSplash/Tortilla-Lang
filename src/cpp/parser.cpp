#include "parser.h"
#include "error.h"
#include <iostream>
//std::make_unique<Node>(line, column, nodeType::Var, DataType::None, DataType::None, "", std::monostate{}, std::monostate{}, false, Assigner::None, std::monostate{});
PrgmNode parse (const std::vector<Token>& code) {
    int i = 0;

    PrgmNode out(0, 0, {}, {});
    while (i < code.size()) {
        out.list.push_back(parseState(code, i));
    }
    return out;
}
node parseState(const std::vector<Token>& code, int& i) {
    std::cout << "\n";
    if (code.at(i).kind == Kind::Keyword) {
        if (isDataType(std::get<Keyword>(code.at(i).val))) {
            return parseAssign(code, i);
        }
    }
    else if (code.at(i).kind == Kind::Stop) {
        ++i;
        return {};
    }
    else if (code.at(i).kind == Kind::Var && code.at(i + 1).kind == Kind::Assigner) {
        return parseAssign(code, i, "?");
    }
    return pratt(code, i, 0);
}
node parseAssign(const std::vector<Token>& code, int& i, const std::string &output) {
    std::string outputDT;
    DataType DT;
    int line = code.at(i).line;
    int column = code.at(i).column;
    std::string Name;
    Assigner Asig;
    node val;
    if (output == "") {
        outputDT = fromKeywords[std::get<Keyword>(code.at(i).val)];
        DT = toDataType.at(std::get<Keyword>(code.at(i).val));
        ++i;//Past DataType
    }
    else {
        outputDT = output;
        DT = DataType::None;
    }
    std::cout << "Assign <" << outputDT << ">";
    std::cout << "[" << std::get<std::string>(code.at(i).val) << "] (";
    if (code.at(i).kind == Kind::Var) {
        Name = std::get<std::string>(code.at(i).val);
    }
    else {
        errorAdd(error::P01, Pass::Parser, code.at(i).line, code.at(i).column);
        Name = "Error";
    }
    ++i; //pass var name
    if (code.at(i).kind == Kind::Assigner) {
        Asig = std::get<Assigner>(code.at(i).val);
        ++i; //pass assigner
        val = pratt(code, i, 0);
    }
    else {
        errorAdd(error::P02, Pass::Parser, code.at(i).line, code.at(i).column);
        Asig = Assigner::None;
        val = {};
    }
    std::cout << ")";
    return std::make_unique<Node>(line, column, nodeType::Assign, DT, DataType::None, Name, std::move(val), std::monostate{}, (outputDT != "?"), Asig, std::monostate{});
}
node parseVar(const std::vector<Token> &code, int& i) {
    std::cout << "Var [" << std::get<std::string>(code.at(i).val) << "]";
    int line = code.at(i).line;
    int column = code.at(i).column;
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
    return std::make_unique<Node>(line, column, nodeType::Var, DataType::None, DataType::None, name, std::monostate{}, std::monostate{}, false, Assigner::None, std::monostate{});
}

node pratt(const std::vector<Token> &code, int &i, const int minBP) {
    if (code.at(i).kind == Kind::Stop) {
        return std::make_unique<Node>(code.at(i).line, code.at(i).column, nodeType::Basic, DataType::None, DataType::None, "", std::monostate{}, std::monostate{}, false, Assigner::None, std::monostate{});
    }
    std::cout << "Pratt(";
    int lineNum = code.at(i).line;
    int columnNum = code.at(i).column;
    Val val = code.at(i).val;
    node left;
    node right;
    if (code.at(i).kind == Kind::Int || code.at(i).kind == Kind::Float || code.at(i).kind == Kind::Bool || code.at(i).kind == Kind::Str) {
        left = std::make_unique<Node>(code.at(i).line, code.at(i).column, nodeType::Basic, kindToDataType[code.at(i).kind], DataType::None, std::get<std::string>(code.at(i).val), std::monostate{}, std::monostate{}, false, Assigner::None, std::monostate{});
        std::cout << " num ";
        //pass num
        ++i;
    }
    else if (code.at(i).kind == Kind::Var) {
        left = parseVar(code, i);
    }
    else if (code.at(i).kind == Kind::Keyword) {
        if (std::get<Keyword>(code.at(i).val) == Keyword::_null) {
            left = std::make_unique<Node>(code.at(i).line, code.at(i).column, nodeType::Basic, DataType::Null, DataType::None, "null", std::monostate{}, std::monostate{}, false, Assigner::None, std::monostate{});
            std::cout << " num ";
            //pass num
            ++i;
        }
    }
    else if (auto* opPtr = std::get_if<Operator>(&code.at(i).val)) {
        if (*opPtr == Operator::Minus || *opPtr == Operator::BitNot) {
            std::cout << " unOp ";
            ++i; // pass operator
            right = pratt(code, i, 90);
            left = std::make_unique<Node>(lineNum, columnNum, nodeType::UnOp, DataType::None, DataType::None, "", std::move(right), std::monostate{}, false, Assigner::None, *opPtr);
        }
        else if (*opPtr == Operator::Lpar) {
            std::vector<node> elems = {};
            bool escape = true;
            bool commas = false;
            ++i;
            while (escape) {
                elems.push_back(pratt(code, i, 0));
                if (auto* opPtr2 = std::get_if<Operator>(&code.at(i).val)) {
                    ++i;
                    if (*opPtr2 == Operator::Rpar) {
                        escape = false;
                    }
                    else {
                        commas = true;
                    }
                }
                if (not commas) {
                    left = std::move(elems.at(0));
                }
            }
        }
    }
    else if (auto* keyPtr = std::get_if<Keyword>(&code.at(i).val)) {
        if (*keyPtr == Keyword::_not) {
            std::cout << " unOp ";
            ++i; //pass operator
            right = pratt(code, i, 90);
            left = std::make_unique<Node>(code.at(i).line, code.at(i).column, nodeType::UnOp, DataType::None, DataType::None, "", std::move(right), std::monostate{}, true, Assigner::None, *keyPtr);
        }
    }
    bool loopCheck = i < code.size();
    while (loopCheck == true) {
        if (BPChart.contains(code.at(i).val) == true) {
            int bp = BPChart.at(code.at(i).val);
            if (minBP <= bp) {
                std::cout << " (Y) ";
                int atOperator = i;
                ++i; //pass operator
                right = pratt(code, i, bp);
                if (i < code.size()) {
                    bool isOpKey = false;
                    if (code.at(atOperator).kind == Kind::Keyword) {
                        isOpKey = true;
                    }
                    left = std::make_unique<Node>(code.at(i).line, code.at(i).column, nodeType::BinOp, DataType::None, DataType::None, "", std::move(left), std::move(right), isOpKey, Assigner::None, code.at(atOperator).val);
                }
                else {
                    left = std::move(right);
                }
                loopCheck = i < code.size();
            }
            else {
                loopCheck = false;
            }
        } else {
            loopCheck = false;
        }
    }
    std::cout << ")";
    return left;
}
