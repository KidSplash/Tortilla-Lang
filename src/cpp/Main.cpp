#include <iostream>
#include <string>

#include "Debug.h"
#include "Common.h"
#include "lexer.h"
#include "error.h"
#include "AST.h"
#include "parser.h"
//#include "Semantic.h"


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
    PrgmNode ast(0, 0, {});
    ast = parse(tokens);
    decodeAST(std::move(ast));
    //std::unordered_map<std::string, Variable> vars = nameCheckAST(std::move(ast));
    //for (const auto& [key, value] : vars) {
        //std::cout << key << "\n";
    //}
    errorsPrint(errorSettings);



    return 0;
}
