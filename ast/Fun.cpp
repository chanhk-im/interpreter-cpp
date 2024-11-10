#include <iostream>

#include "Fun.h"

using namespace std;

Fun::Fun(string param, AST *body) {
    this->param = param;
    this->body = body;
    this->setType(FUN);
}
string Fun::getParam() {
    return param;
}
AST *Fun::getBody() {
    return body;
}
string Fun::getASTCode() {
    string astCode;
    astCode += "(fun ";
    astCode += param;
    astCode += " ";
    astCode += body->getASTCode();
    astCode += ")";

    return astCode;
}
AST *Fun::copyAST() {
    Fun *newFun = new Fun(param, body->copyAST());
    return newFun;
}
