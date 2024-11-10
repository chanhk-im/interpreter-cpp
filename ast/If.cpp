#include "If.h"

#include <iostream>

using namespace std;

If::If(AST *condExpr, AST *thenExpr, AST *elseExpr) {
    this->condExpr = condExpr;
    this->thenExpr = thenExpr;
    this->elseExpr = elseExpr;
    setType(IF);
}
AST *If::getCondExpr() {
    return condExpr;
}
AST *If::getThenExpr() { return thenExpr; }
AST *If::getElseExpr() { return elseExpr; }
string If::getASTCode() {
    string astCode;
    astCode += "(if ";
    astCode += condExpr->getASTCode();
    astCode += " ";
    astCode += thenExpr->getASTCode();
    astCode += " ";
    astCode += elseExpr->getASTCode();
    astCode += ")";
    return astCode;
}
AST *If::copyAST() {
    If *newIf = new If(condExpr->copyAST(), thenExpr->copyAST(), elseExpr->copyAST());
    return newIf;
};