#ifndef _SUB_H_
#define _SUB_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Sub : public AST {
   private:
    AST *lhs;
    AST *rhs;

   public:
    Sub(AST *lhs, AST *rhs);
    AST *getLhs();
    AST *getRhs();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif