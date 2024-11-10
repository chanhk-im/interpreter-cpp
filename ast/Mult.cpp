#include "Mult.h"

#include <iostream>

using namespace std;

Mult::Mult(AST *lhs, AST *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
    setType(MULT);
}

AST *Mult::getLhs() { return lhs; }

AST *Mult::getRhs() { return rhs; }

string Mult::getASTCode() {
    string astCode;
    astCode += "(mult ";
    astCode += lhs->getASTCode();
    astCode += " ";
    astCode += rhs->getASTCode();
    astCode += ")";

    return astCode;
}

AST *Mult::copyAST() {
    Mult *newMult = new Mult(lhs->copyAST(), rhs->copyAST());
    return newMult;
}