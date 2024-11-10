#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>

#include "ast/AST.h"

class Parser {
   public:
    AST *parse(string sexp);
    vector<string> splitExpressionAsSubExpressions(string sexp);
    vector<string> getSubExpressions(string sexp);
    bool isNumeric(string str);
    bool isList(string str);
    bool isRecursion(string sexp);
    string desugar(string sexp);
};

#endif