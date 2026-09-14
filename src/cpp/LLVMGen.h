#ifndef TORTILLA_LLVMGEN_H
#define TORTILLA_LLVMGEN_H
#include <string>
#include "Common.h"
#include "AST.h"

enum class subType {
    alloca,
    load,
    store,
    BitNot,
    Not,
    Negative,
    Plus,
    Minus,
    Times,
    Divide,
    Modulo,
    Power,
    And,
    Or,
    Xor,
    BitAnd,
    BitOr,
    BitXor,
    Less,
    More,
    Gte,
    Lte,
    Is,
};

void subfunct();

void genCode(PrgmNode node);
void genPrgm(PrgmNode node);
std::string genNode(Node& node, std::string name, DataType DT);
std::string genAssign(Node& node);
std::string genBinOp(Node& node, std::string name, DataType DT);
std::string genUnOp(Node& node, std::string name, DataType DT);
std::string genBasic(Node& node);
std::string genVar(Node& node);

#endif