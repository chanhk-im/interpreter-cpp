#include "Or.h"

#include <iostream>

using namespace std;

Or::Or(AST *lCond, AST *rCond) {
    this->lCond = lCond;
    this->rCond = rCond;
    setType(OR);
}
AST *Or::getLCond() {
    return lCond;
}
AST *Or::getRCond() {
    return rCond;
}
string Or::getASTCode() {
    string astCode;
    astCode += "(or ";
    astCode += lCond->getASTCode();
    astCode += " ";
    astCode += rCond->getASTCode();
    astCode += ")";
    return astCode;
}
AST *Or::copyAST() {
    Or *newOr = new Or(lCond->copyAST(), rCond->copyAST());
    return newOr;
};