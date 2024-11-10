#ifndef _ADD_H_
#define _ADD_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Add : public AST {
   private:
    AST *lhs;
    AST *rhs;

   public:
    Add(AST *lhs, AST *rhs);
    AST *getLhs();
    AST *getRhs();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif