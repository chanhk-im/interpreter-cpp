#ifndef _EQ_H_
#define _EQ_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Eq : public AST {
   private:
    AST *lhs;
    AST *rhs;

   public:
    Eq(AST *lhs, AST *rhs);
    AST *getLhs();
    AST *getRhs();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif