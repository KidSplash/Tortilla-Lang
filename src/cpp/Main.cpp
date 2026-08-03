#include <iostream>
#include <string>

#include "Debug.h"
#include "Common.h"
#include "lexer.h"
#include "error.h"
#include "AST.h"
#include "parser.h"
#include "Semantic.h"

//TODO: Fix Name Checker overuse of N01 error. Test Type Checker.
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
    PrgmNode ast1(0, 0, {});
    ast1 = parse(tokens);
    //decodeAST(std::move(ast1));
    struct AST ast2 = nameCheckAST(std::move(ast1));
    //struct AST ast3 = typeCheckAST(std::move(ast2.ast));
    errorsPrint(errorSettings);



    return 0;
}
