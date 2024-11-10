#include <iostream>

#include "App.h"

using namespace std;

App::App(AST *ftn, AST *arg) {
    this->ftn = ftn;
    this->arg = arg;
    this->setType(APP);
}
AST *App::getFtn() {
    return ftn;
}
AST *App::getArg() {
    return arg;
}
string App::getASTCode() {
    string astCode;
    astCode += "(app ";
    astCode += ftn->getASTCode();
    astCode += " ";
    astCode += arg->getASTCode();
    astCode += ")";

    return astCode;
}
AST *App::copyAST() {
    App *newApp = new App(ftn->copyAST(), arg->copyAST());
    return newApp;
}
