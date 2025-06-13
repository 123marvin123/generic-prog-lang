#pragma once

#include "antlr4-runtime.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class CustomErrorListener final : public antlr4::BaseErrorListener
{
public:
    CustomErrorListener() {}

    void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override;
};
