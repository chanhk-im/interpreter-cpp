#include "Id.h"

#include <iostream>

using namespace std;

Id::Id(string name) {
    this->name = name;
    this->setType(ID);
}
string Id::getName() { return name; }
string Id::getASTCode() {
    string astCode;
    astCode += "(id ";
    astCode += name;
    astCode += ")";
    return astCode;
}
AST *Id::copyAST() {
    Id *newId = new Id(name);
    return newId;
};