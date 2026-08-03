#ifndef TORTILLA_ERROR_H
#define TORTILLA_ERROR_H

#pragma once

#include "Common.h"

enum class error {
    L01,
    L02,
    L03,
    L04,
    P01,
    P02,
    N01,
    N02,
    T01,
    T02,
    T03,
    A00,
};

class Error {
public:
    int level;
    error type;
    Pass from;
    int line;
    int column;
    std::string message;
    Error(error t, Pass f, int li, int c, int le, std::string m);
};

void errorAdd(error type, Pass from, int line, int column);

void errorsPrint(std::vector<bool> settings);

#endif