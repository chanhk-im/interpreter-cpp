#include <iostream>

#include "With.h"

using namespace std;

With::With(string name, AST *namedExpr, AST *body) {
    this->name = name;
    this->namedExpr = namedExpr;
    this->body = body;
    this->setType(WITH);
}

string With::getName() {
    return name;
}

AST *With::getNamedExpr() {
    return namedExpr;
}

AST *With::getBody() {
    return body;
}

string With::getASTCode() {
    string astCode;
    astCode += "(with \'";
    astCode += name;
    astCode += " ";
    astCode += namedExpr->getASTCode();
    astCode += " ";
    astCode += body->getASTCode();
    astCode += ")";

    return astCode;
}

AST *With::copyAST() {
    With *newWith = new With(name, namedExpr->copyAST(), body->copyAST());
    return newWith;
}