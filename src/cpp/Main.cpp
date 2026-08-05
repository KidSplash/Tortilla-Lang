#include <iostream>
#include <string>

#include "Common.h"
#include "lexer.h"
#include "error.h"
#include "AST.h"
#include "parser.h"
#include "Semantic.h"
//TODO: Use std::unique_ptr<Node> instead of variant node in all cases
int main() {
    std::string code = R"(
#Comment Test
int a = 0
int b = 15.5
float c = (a + b) * 10
float d= 4.1
char e = "a"
bool f = 0
bool g = false
a = 15
b = 10.1
c = b / a
d = "dfads"
)";
    //std::cout << std::to_string(code.length()) << " " << code.at(17);
    /*
    *#Comment Test
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
    */


    std::vector<Token> tokens = tokenize(code);
    //decodeTokens(tokens);
    PrgmNode ast1(0, 0, {}, {});
    ast1 = parse(tokens);
    std::unordered_map<std::string, Variable> globals = {};
    AST ast2 = nameCheckPrgm(std::move(ast1), globals);
    //struct AST ast3 = typeCheckAST(std::move(ast2));
    errorsPrint(errorSettings);
    for (const auto& [key, value] : ast2.globals) {
        std::cout << key << '\n';
    }

    return 0;
}
