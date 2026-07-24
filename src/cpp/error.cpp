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
            message.append("Unterminated ## Comment.\n");
            break;
        case (error::L02):
            message.append("Unterminated String.\n");
            break;
        default:
            message.append("Even we don't know what you did wrong.\n");
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