#include "Sub.h"

#include <iostream>

using namespace std;

Sub::Sub(AST *lhs, AST *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
    setType(SUB);
}

AST *Sub::getLhs() { return lhs; }

AST *Sub::getRhs() { return rhs; }

string Sub::getASTCode() {
    string astCode;
    astCode += "(sub ";
    astCode += lhs->getASTCode();
    astCode += " ";
    astCode += rhs->getASTCode();
    astCode += ")";

    return astCode;
}

AST *Sub::copyAST() {
    Sub *newSub = new Sub(lhs->copyAST(), rhs->copyAST());
    return newSub;
}