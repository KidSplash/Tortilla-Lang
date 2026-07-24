#include "lexer.h"
#include "error.h"
#include <cctype>
using namespace std;

Token::Token(const Kind k, const Val &v, const int l, const int c) {
    kind = k;
    val = v;
    line = l;
    column = c;
};

vector<Token> tokenize(const string& code) {
    int i = 0;
    int mode = 0; //0 = Normal, 1 = Single-line Comment, 2 = Multi-line Comment, 3 = String
    int line = 0;
    int column = 0;
    int tabWidth = 2;
    char qotType = ' ';  //Current quotation Type for Strings
    vector<Token> tokens;
    string value;

    while (i < code.length()) {
        //Increment line
        if (code[i] == '\n') {
            line += 1;
            column = 0;
        }
        if (code[i] == '\t') {
            column += tabWidth;
        }

        //Exiting Comments
        if (mode == 1 or mode == 2) {
            //Escape Single-Line Comment
            if (mode == 1 and code[i] == '\n') {
                ++i;
                ++column;
                mode = 0;
            }//Escape Multi-Line Comment
            else if (i + 1 < code.length() and code[i] == '#' and code[i + 1] == '#') {
                i += 2;
                column += 2;
                mode = 0;
            }
        }
        //Normal Mode
        else if (mode == 0) {
            //[]\;,.~@$()_{}:?  <those symbols cannot be used outside of strings (except "." can be used in numbers)
            if (isspace(code[i])) {
                ++i;
                ++column;
                if (i > code.length()){ return tokens; }
            }
            else if (code[i] == '#') {
                ++i;
                ++column;
                if (i <= code.length() and code[i] == '#') {
                    mode = 2;
                    ++i;
                    ++column;
                }
                else {
                    mode = 1;
                }
            }
            //Checks for Number Literals
            else if (isdigit(code[i])) {
                //If point becomes True, number is a float
                bool point = false;
                int start = i;
                ++i;
                ++column;
                while (i <= code.length() and (isdigit(code[i]) or code[i] == '.')) {
                    if (code[i] == '.'){
                        if (point == true){
                            //error
                        }
                        point = true;
                    }
                    ++i;
                    ++column;
                }
                std::string num = std::string(code).substr(start, i - start);
                Token curTok = Token(point ? Kind::Float : Kind::Int, num, line, column);
                tokens.push_back(curTok);
            }
            //Starts a String
            else if (code[i] == '`' or code[i] == '\'' or code[i] == '\"') {
                mode = 3;
                //Type of quote to look for
                qotType = code[i];
                ++i;
                ++column;
            }
            else if (code[i] == '=' and code[i + 1] != '=') {
                Token curTok = Token(Kind::Assigner, Assigner::Assign, line, column);
                tokens.push_back(curTok);
                ++i;
                ++column;
            }
            else if (getDoubOp(code[i], code[i + 1]) != Operator::None) {
                Token curTok = Token(Kind::Operator, getDoubOp(code[i], code[i + 1]), line, column);
                tokens.push_back(curTok);
                i += 2;
                column += 2;
            }
            else if (getAsig(code[i], code[i + 1]) != Assigner::None) {
                Token curTok = Token(Kind::Assigner, getAsig(code[i], code[i + 1]), line, column);
                tokens.push_back(curTok);
                i += 2;
                column += 2;
            }
            else if (getSingOp(code[i]) != Operator::None) {
                Token curTok = Token(Kind::Operator, getSingOp(code[i]), line, column);
                tokens.push_back(curTok);
                ++i;
                ++column;
            }
            else if (isalpha(code[i])) {
                string word;
                int start = i;
                Val token_value;
                Kind kind;
                ++i;
                ++column;
                //Adds characters to the word until it finds a non number, letter, or underspace
                while (i <= code.length() and (isalnum(code[i]) or code[i] == '_')) {
                    ++i;
                    ++column;
                }
                if (code.substr(start, i - start) == "true" or code.substr(start, i - start) == "false") {
                    kind = Kind::Bool;
                    token_value = code.substr(start, i - start);
                }
                else if (keywords.contains(code.substr(start, i - start))) {
                    kind = Kind::Keyword;
                    token_value = keywords.at(code.substr(start, i - start));
                }
                else {
                    kind = Kind::Var;
                    token_value = code.substr(start, i - start);
                }
                Token curTok = Token(kind, token_value, line, column);
                tokens.push_back(curTok);
            }
            else {
                //error
            }
        }
        //Go through String or Comment
        else if (i <= code.length()) {
            //Repeats until it finds the correct end quote
            if (code[i] == qotType) {
                Token curTok = Token(Kind::Str, value, line, column);
                tokens.push_back(curTok);
                value = " ";
                mode = 0;
            }
            else {
                value += code[i];
            }
            ++i;
            ++column;
        }
    }
    tokens.push_back(Token(Kind::Stop, "", 0, 0));
    return tokens;
}