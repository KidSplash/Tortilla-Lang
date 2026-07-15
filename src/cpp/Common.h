#ifndef TORTILLA_COMMON_H
#define TORTILLA_COMMON_H
#pragma once

#include <variant>
#include <string>
#include <unordered_map>
//#include <typeinfo>
#include <iostream>

enum class Kind {
    Var,
    Keyword,
    Operator,
    Assigner,
    Int,
    Float,
    Bool,
    Str
};
enum class Operator {
    Plus, Times, Minus, Divide, Mod,
    BitNot, BitAnd, BitXor, BitOr, Lpar, Rpar,
    Lbrc, Rbrc, Lbrkt, Rbrkt, Then, Point, Semi,
    Comma, More, Less, None, Power,
    Shl, Shr, Gte, Lte,
};
enum class Assigner {
    Assign, Inc, PlusEql, MinusEql,
    Dec, DivideEql, ModEql, None, TimesEql,
};
enum class Keyword {
    _is, _not, _in, _has, _xor, _nor, _and,
    _or, _null, _int, _bigint, _float, _doub,
    _char, _str, _bool, _array, _set, _dict,
    _class, _func, _if, _elif, _else, _switch,
    _case, _default, _for, _while, _forEach,
    _return, _out, _self, _const, _type, _label,
    _goto
};
enum class DataType {
    Int, Bool, Bigint, Float, Doub, Char, Null,
};

using Val = std::variant<std::string, Operator, Assigner, Keyword, int>;

class Token {
public:
    Kind kind;
    Val val; //Value or specific type e.g. kind = Operator, val = 'Plus'
    int line; //Line number
    Token(Kind k, const Val &v, int l);
};

inline bool isDataType (Keyword word) {
    switch (word) {
        case Keyword::_int:
        case Keyword::_float:
        case Keyword::_bigint:
        case Keyword::_doub:
        case Keyword::_bool:
        case Keyword::_char:
        case Keyword::_null:
            return true;
        default:
            return false;
    }
}
inline std::unordered_map<Keyword, DataType> toDataType {
        {Keyword::_int, DataType::Int},
        {Keyword::_bigint, DataType::Bigint},
        {Keyword::_float, DataType::Float},
        {Keyword::_doub, DataType::Doub},
        {Keyword::_char, DataType::Char},
        {Keyword::_bool, DataType::Bool},
        {Keyword::_null, DataType::Null}
};
inline std::unordered_map<DataType, std::string> fromDataType {
    {DataType::Int, "int"},
    {DataType::Bigint, "bigint"},
    {DataType::Bool, "cool"},
    {DataType::Char, "char"},
    {DataType::Float, "float"},
    {DataType::Doub, "doub"},
    {DataType::Null, "null"},
};
inline std::unordered_map<Val, int> BPChart {
    {Assigner::Assign, 10},
    {Assigner::PlusEql, 10},
    {Assigner::MinusEql, 10},
    {Assigner::TimesEql, 10},
    {Assigner::DivideEql, 10},
    {Assigner::ModEql, 10},
    {Assigner::Inc, 10},
    {Assigner::Dec, 10},
    {Keyword::_and, 20},
    {Keyword::_or, 20},
    {Keyword::_xor, 20},
    {Keyword::_nor, 20},
    {Keyword::_is, 30},
    {Operator::Less, 30},
    {Operator::More, 30},
    {Operator::Lte, 30},
    {Operator::Gte, 30},
    {Keyword::_in, 30},
    {Keyword::_has, 30},
    {Operator::BitAnd, 40},
    {Operator::BitOr, 40},
    {Operator::BitXor, 40},
    {Operator::Shl, 50},
    {Operator::Shr, 50},
    {Operator::Plus, 60},
    {Operator::Minus, 60},
    {Operator::Mod, 70},
    {Operator::Divide, 70},
    {Operator::Times, 70},
    {Operator::Power, 80},
    {Operator::Point, 100},
    {Operator::Lbrc, 100},
    {Operator::Lpar, 100},
};
inline std::unordered_map<Kind, std::string> fromKind {
    {Kind::Assigner, "Assigner"},
    {Kind::Operator, "Operator"},
    {Kind::Bool, "Bool"},
    {Kind::Int, "Int"},
    {Kind::Float, "Float"},
    {Kind::Var, "Var"},
    {Kind::Keyword, "Keyword"},
    {Kind::Str, "Str"},
};
inline std::unordered_map<std::string, Keyword> keywords {
        {"is", Keyword::_is},
        {"not", Keyword::_not},
        {"in", Keyword::_in},
        {"has", Keyword::_has},
        {"xor", Keyword::_xor},
        {"nor", Keyword::_nor},
        {"and", Keyword::_and},
        {"or", Keyword::_or},
        {"null", Keyword::_null},
        {"int", Keyword::_int},
        {"bigint", Keyword::_bigint},
        {"float", Keyword::_float},
        {"doub", Keyword::_doub},
        {"char", Keyword::_char},
        {"str", Keyword::_str},
        {"bool", Keyword::_bool},
        {"array", Keyword::_array},
        {"set", Keyword::_set},
        {"dict", Keyword::_dict},
        {"class", Keyword::_class},
        {"func", Keyword::_func},
        {"if", Keyword::_if},
        {"elif", Keyword::_elif},
        {"else", Keyword::_else},
        {"switch", Keyword::_switch},
        {"case", Keyword::_case},
        {"default", Keyword::_default},
        {"for", Keyword::_for},
        {"while", Keyword::_while},
        {"forEach", Keyword::_forEach},
        {"return", Keyword::_return},
        {"out", Keyword::_out},
        {"self", Keyword::_self},
        {"const", Keyword::_const},
        {"type", Keyword::_type},
        {"label", Keyword::_label},
        {"goto", Keyword::_goto},
    };
inline std::unordered_map<Keyword, std::string> fromKeywords {
        {Keyword::_is, "is"},
        {Keyword::_not, "not"},
        {Keyword::_in, "in"},
        {Keyword::_has, "has"},
        {Keyword::_xor, "xor", },
        {Keyword::_nor, "nor"},
        {Keyword::_and, "and"},
        {Keyword::_or, "or"},
        {Keyword::_null, "null"},
        {Keyword::_int, "int"},
        {Keyword::_bigint, "bigint"},
        {Keyword::_float, "float"},
        {Keyword::_doub, "doub"},
        {Keyword::_char, "char"},
        {Keyword::_str, "str"},
        {Keyword::_bool, "bool"},
        //{"array", Keyword::_array},
        //{"set", Keyword::_set},
        //{"dict", Keyword::_dict},
        //{"class", Keyword::_class},
        //{"func", Keyword::_func},
        //{"if", Keyword::_if},
        //{"elif", Keyword::_elif},
        //{"else", Keyword::_else},
        {Keyword::_switch, "switch"},
        {Keyword::_case, "case"},
        {Keyword::_default, "default"},
        {Keyword::_for, "for"},
        {Keyword::_while, "while", },
        {Keyword::_forEach, "forEach", },
        {Keyword::_return, "return", },
        {Keyword::_out, "out"},
        {Keyword::_self, "self"},
        {Keyword::_const, "const"},
        {Keyword::_type, "type", },
        {Keyword::_label, "label"},
        {Keyword::_goto, "goto"},
    };
inline Operator getSingOp(char c) {
    switch(c) {
        case '+': return Operator::Plus;
        case '*': return Operator::Times;
        case '-': return Operator::Minus;
        case '/': return Operator::Divide;
        case '%': return Operator::Mod;
        case '!': return Operator::BitNot;
        case '&': return Operator::BitAnd;
        case '^': return Operator::BitXor;
        case '|': return Operator::BitOr;
        case '(': return Operator::Lpar;
        case ')': return Operator::Rpar;
        case '[': return Operator::Lbrc;
        case ']': return Operator::Rbrc;
        case '<': return Operator::Less;
        case '>': return Operator::More;
        case '{': return Operator::Lbrkt;
        case '}': return Operator::Rbrkt;
        case ':': return Operator::Then;
        case '.': return Operator::Point;
        case ';': return Operator::Semi;
        case ',': return Operator::Comma;
        default: return Operator::None;
    }
}
inline Operator getDoubOp(char first, char second) {
    switch(first) {
        case '*':
            if (second == '*'){ return Operator::Power; }
            else { return Operator::None; }
        case '<':
            switch(second) {
            case '=': return Operator::Lte;
            case '<': return Operator::Shl;
            default:  return Operator::None;
            }
        case '>':
            switch(second) {
            case '=': return Operator::Gte;
            case '>': return Operator::Shr;
            default:  return Operator::None;
            }
        default: return Operator::None;
    }
}
inline Assigner getAsig(char first, char second) {
    switch (first) {
        case '+':
            switch (second) {
            case '=': return Assigner::PlusEql;
            case '+': return Assigner::Inc;
            default: return Assigner::None;
            }
        case '-':
            switch (second) {
            case '=': return Assigner::MinusEql;
            case '-': return Assigner::Dec;
            default: return Assigner::None;
            }
        case '/':
            if (second == '='){return Assigner::DivideEql; }
            else { return Assigner::None; }
        case '*':
            if (second == '='){ return Assigner::TimesEql; }
            else { return Assigner::None; }
        case '%':
            if (second == '='){ return Assigner::ModEql; }
            else { return Assigner::None; }
        default:
            return Assigner::None;
    }
}
inline std::unordered_map<Operator, std::string> fromOperator {
    {Operator::BitAnd, "&"},
    {Operator::BitOr, "|"},
    {Operator::Shr, ">>"},
    {Operator::Shl, "<<"},
    {Operator::Power, "**"},
    {Operator::None, "NONE"},
    {Operator::Rbrkt, "}"},
    {Operator::Lbrkt, "{"},
    {Operator::Rbrc, "]"},
    {Operator::Lbrc, "["},
    {Operator::Rpar, ")"},
    {Operator::Lpar, "("},
    {Operator::Minus, "-"},
    {Operator::Plus, "+"},
    {Operator::Mod, "%"},
    {Operator::Times, "*"},
    {Operator::Divide, "/"},
    {Operator::Then, ":"},
    {Operator::Semi, ";"},
    {Operator::Comma, ","},
    {Operator::More, "<"},
    {Operator::Less, "<"},
    {Operator::Lte, "<="},
    {Operator::Gte, ">="},
    {Operator::BitXor, "^"},
    {Operator::BitNot, "!"}
};


//Decoding
inline void decodeToken(Token token) {
    std::cout << fromKind[token.kind];
    if (token.kind == Kind::Float || token.kind == Kind::Int
|| token.kind == Kind::Bool || token.kind == Kind::Var || token.kind == Kind::Str) {
        std::cout << ": " << std::get<std::string>(token.val);
    }
    else if (token.kind == Kind::Keyword) {
        std::cout << ": " << fromKeywords[std::get<Keyword>(token.val)];
    }
    std::cout << "\n";
}
inline void decodeTokens(std::vector<Token> tokens) {
    int i = 0;
    while (i < tokens.size()) {
        decodeToken(tokens[i]);

        ++i;
    }
}

#endif

//TODO: Make sure VarNode only needs a name input
//TODO: Finish Phase 1 of Parser and then move onto Hoisters, Name Checker, Type Checker