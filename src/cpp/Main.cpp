#include <iostream>
#include <string>

#include "Debug.h"
#include "lexer.h"
#include "AST.h"
#include "parser.h"
#include "Semantic.h"


int main() {
    std::string code = R"(
#Comment Test
int a = 0
int b = 15.5
float c =12
float d= 4.1
char word = "a"
bool notABool = 0
bool aBool = false
a = null
b += aBool
word = word + word
##Heres another
comment##
aBool = not aBool
c = b / a
)";

    std::vector<Token> tokens = tokenize(code);
    //decodeTokens(tokens);
    //std::cout << "\n\n";
    //PrgmNode ast(0, {});
    //ast = parse(tokens);
    //decodeAST(std::move(ast));
    //std::unordered_map<std::string, Variable> vars = nameCheckAST(std::move(ast));
    //for (const auto& [key, value] : vars) {
        //std::cout << key << "\n";
    //}



    return 0;
}
