#include <iostream>
#include <string>

#include "Debug.h"
#include "lexer.h"
#include "AST.h"
#include "parser.h"


int main() {
    std::string code = R"(
int a = 0
int b = a + 5
a += b * -10
char c = "h"
)";
    std::vector<Token> tokens = tokenize(code);
    //decodeTokens(tokens);
    //std::cout << "\n\n";
    PrgmNode ast(0, {});
    ast = parse(tokens);
    decodeAST(std::move(ast));
    return 0;
}
