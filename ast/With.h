#ifndef _WITH_H_
#define _WITH_H_

#include <iostream>

#include "AST.h"

using namespace std;

class With : public AST {
   private:
    string name;
    AST *namedExpr;
    AST *body;

   public:
    With(string name, AST *namedExpr, AST *body);
    string getName();
    AST *getNamedExpr();
    AST *getBody();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif