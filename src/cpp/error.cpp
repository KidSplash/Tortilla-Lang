#include "error.h"
#include <vector>
#include <string>

Error::Error(error t, Pass f, int li, int c, int le, std::string m) {
    type = t;
    from = f;
    line = li;
    column = c;
    message = m;
    level = le;
};

std::vector<Error> errors {};

void errorAdd(error type, Pass from, int line, int column) {
    std::string message = "";
    int level = 0;
    switch (type) {
        case (error::L01):
            message.append("Unterminated ## Comment. ");
            break;
        case (error::L02):
            message.append("Unterminated String. ");
            break;
        case (error::L03):
            message.append("Cannot have multiple \".\" in the same number. ");
            break;
        case (error::L04):
            message.append("Unkown Symbol. ");
            break;
        case (error::P01):
            message.append("Expected Variable Name. ");
            break;
        case (error::P02):
            message.append("Expected Assignment Operator. ");
            break;
        case (error::N01):
            message.append("Variable has already been declared. ");
            break;
        case (error::N02):
            message.append("Variable has not been declared. ");
            break;
        case (error::T01):
            message.append("Variable value doesn't match declared DataType. ");
            break;
        case (error::T02):
            message.append("This Operator cannot operate on non-numbers. ");
            break;
        default:
            message.append("Even we don't know what you did wrong. ");
            level = 3;
    }
    message.append("Line: " + std::to_string(line) + ", Column: " + std::to_string(column) + ". In pass " + fromPass[from] + "\n");
    errors.push_back(Error(type, from, line, column, level, message));
}

void errorsPrint(std::vector<bool> settings) {
    int i = 0;
    while (i < errors.size()) {
        if (settings.at(errors.at(i).level) == true) {
            std::cout << errors.at(i).message;
        }
        ++i;
    }
}