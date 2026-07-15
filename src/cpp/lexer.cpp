#include "lexer.h"
#include "error.h"
#include <cctype>
using namespace std;

Token::Token(const Kind k, const Val &v, const int l) {
    kind = k;
    val = v;
    line = l;
};

vector<Token> tokenize(const string& code) {
    int i = 0;
    int mode = 0; //0 = Normal, 1 = Single-line Comment, 2 = Multi-line Comment, 3 = String
    int line = 0;
    char qot = ' ';  //Quotation Type for Strings
    vector<Token> tokens;
    string value;
    //code += " ";  //Adds an ending space to the code so that the index does not go out of bounds

    while (i < code.length()) {
        //Increment line
        if (code[i] == '\n') {
            line += 1;
        }

        //Comment Removal
        if (mode == 1 or mode == 2) {
            if (mode == 1 and code[i] == '\n') {
                i += 1;
                mode = 0;
            }
            else if (i + 1 < code.length() and code[i] == '#' and code[i + 1] == '#') {
                i += 2;
                mode = 0;
            }
        }
        //Normal Mode
        else if (mode == 0) {
            if (isspace(code[i])) {
                i += 1;
                if (i > code.length()){ return tokens; }
            }
            else if (code[i] == '#') {
                i += 1;
                if (i <= code.length() and code[i] == '#') {
                    mode = 2;
                    i += 1;
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
                i += 1;
                while (i <= code.length() and (isdigit(code[i]) or code[i] == '.')) {
                    if (code[i] == '.'){
                        if (point == true){
                            addError ("hard", 2, line, {});
                        }
                        point = true;
                    }
                    i += 1;
                }
                std::string num = std::string(code).substr(start, i - start);
                Token curTok = Token(point ? Kind::Float : Kind::Int, num, line);
                tokens.push_back(curTok);
            }
            //Starts a String
            else if (code[i] == '`' or code[i] == '\'' or code[i] == '\"') {
                mode = 3;
                //Type of quote to look for
                qot = code[i];
                i += 1;
            }
            else if (code[i] == '=' and code[i + 1] != '=') {
                Token curTok = Token(Kind::Assigner, Assigner::Assign, line);
                tokens.push_back(curTok);
                ++i;
            }
            else if (getDoubOp(code[i], code[i + 1]) != Operator::None) {
                Token curTok = Token(Kind::Operator, getDoubOp(code[i], code[i + 1]), line);
                tokens.push_back(curTok);
                i += 2;
            }
            else if (getAsig(code[i], code[i + 1]) != Assigner::None) {
                Token curTok = Token(Kind::Assigner, getAsig(code[i], code[i + 1]), line);
                tokens.push_back(curTok);
                i += 2;
            }
            else if (getSingOp(code[i]) != Operator::None) {
                Token curTok = Token(Kind::Operator, getSingOp(code[i]), line);
                tokens.push_back(curTok);
                i += 1;
            }
            else if (isalpha(code[i])) {
                string word;
                int start = i;
                Val token_value;
                Kind kind;
                i += 1;
                //Adds characters to the word until it finds a non number, letter, or underspace
                while (i <= code.length() and (isalnum(code[i]) or code[i] == '_')) {
                    i += 1;
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
                Token curTok = Token(kind, token_value, line);
                tokens.push_back(curTok);
            }
            else {
                addError("soft", 1, line, {to_string(code[i])});
            }
        }
        //String Mode
        else if (i <= code.length()) {
            //Repeats until it finds the correct end quote
            if (code[i] == qot) {
                Token curTok = Token(Kind::Str, value, line);
                tokens.push_back(curTok);
                value = " ";
                mode = 0;
            }
            else {
                value += code[i];
            }
            i += 1;
        }
    }
    return tokens;
}