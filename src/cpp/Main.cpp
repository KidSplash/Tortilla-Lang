#include <iostream>
#include <string>

#include "Debug.h"
#include "lexer.h"
#include "AST.h"
#include "parser.h"
#include "Semantic.h"


int main() {
    std::string code = R"(
int a = 0
int b = a + 5
a += b * -10
char c = "h"
bool question = true
question = not question
thisisafloat -= 17.1
)";

    std::vector<Token> tokens = tokenize(code);
    //decodeTokens(tokens);
    //std::cout << "\n\n";
    PrgmNode ast(0, {});
    ast = parse(tokens);
    //decodeAST(std::move(ast));
    std::unordered_map<std::string, Variable> vars = nameCheckAST(std::move(ast));

    //for (const auto& [key, value] : vars) {
        //std::cout << key << "\n";
    //}

    return 0;
}
