#pragma once

#include <cmath>

#include "muparser/muParser.h"


mu::Parser *parseFunction(const std::string& function, double* varX) {
    try {
        mu::Parser *parser = new mu::Parser();
        parser->DefineVar("x", varX);
        parser->SetExpr(function);
        parser->Eval();
        return parser;
    } catch (mu::Parser::exception_type &e) {
        return nullptr;
    }
}

