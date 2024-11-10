#include "Eq.h"

#include <iostream>

using namespace std;

Eq::Eq(AST *lhs, AST *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
    setType(EQ);
}

AST *Eq::getLhs() { return lhs; }

AST *Eq::getRhs() { return rhs; }

string Eq::getASTCode() {
    string astCode;
    astCode += "(eq ";
    astCode += lhs->getASTCode();
    astCode += " ";
    astCode += rhs->getASTCode();
    astCode += ")";

    return astCode;
}

AST *Eq::copyAST() {
    Eq *newEq = new Eq(lhs->copyAST(), rhs->copyAST());
    return newEq;
}