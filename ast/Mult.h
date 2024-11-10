#ifndef _MULT_H_
#define _MULT_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Mult : public AST {
   private:
    AST *lhs;
    AST *rhs;

   public:
    Mult(AST *lhs, AST *rhs);
    AST *getLhs();
    AST *getRhs();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif