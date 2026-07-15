#ifndef TORTILLA_LANG_LEXER_H
#define TORTILLA_LANG_LEXER_H
#pragma once

#include "Common.h"
#include <vector>

Operator getSingOp(char c);
Operator getDoubOp(char first, char second);
Assigner getAsig(char first, char second);

std::vector<Token> tokenize(const std::string& code);

#endif