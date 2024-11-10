#ifndef _IF_H_
#define _IF_H_

#include <iostream>

#include "AST.h"

using namespace std;

class If : public AST {
   private:
    AST *condExpr;
    AST *thenExpr;
    AST *elseExpr;

   public:
    If(AST *condExpr, AST *thenExpr, AST *elseExpr);
    AST *getCondExpr();
    AST *getThenExpr();
    AST *getElseExpr();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif