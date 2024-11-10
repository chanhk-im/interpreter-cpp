#include "Add.h"

#include <iostream>

using namespace std;

Add::Add(AST *lhs, AST *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
    setType(ADD);
}

AST *Add::getLhs() { return lhs; }

AST *Add::getRhs() { return rhs; }

string Add::getASTCode() {
    string astCode;
    astCode += "(add ";
    astCode += lhs->getASTCode();
    astCode += " ";
    astCode += rhs->getASTCode();
    astCode += ")";

    return astCode;
}

AST *Add::copyAST() {
    Add *newAdd = new Add(lhs->copyAST(), rhs->copyAST());
    return newAdd;
}