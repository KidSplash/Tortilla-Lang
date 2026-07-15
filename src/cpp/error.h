#ifndef TORTILLA_ERROR_H
#define TORTILLA_ERROR_H
#include <vector>
#include <string>

class Error {
    public:
        std::string kind;  //soft hard
        std::string message;
        int numb;
        int line;
        Error(std::string k, std::string m, int n, int l);
};

void readErrors();
void addError(std::string kind, int numb, int line, std::vector<std::string> vals);
bool hasHard();

#endif