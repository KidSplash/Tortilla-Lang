#ifndef TORTILLA_LANG_LEXER_H
#define TORTILLA_LANG_LEXER_H
#pragma once

#include "Common.h"
#include <vector>

std::vector<Token> tokenize(const std::string& code);

#endif