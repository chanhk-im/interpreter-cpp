#include "Num.h"

#include <iostream>

using namespace std;

Num::Num(string num) {
    setType(NUM);
    this->num = num;
}

string Num::getNum() { return num; }

string Num::getASTCode() {
    string astCode;
    astCode += "(num ";
    astCode += num;
    astCode += ")";
    return astCode;
}

AST *Num::copyAST() {
    Num *newNum = new Num(num);
    return newNum;
}