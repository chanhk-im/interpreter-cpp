#include "AST.h"

#include <iostream>

using namespace std;

string AST::getASTCode() { return "()"; }
AST *AST::copyAST() {
    AST *newAST = new AST;
    newAST->setType(NUL);
    return newAST;
}
typeNum AST::getType() { return type; }
void AST::setType(typeNum to) { type = to; }