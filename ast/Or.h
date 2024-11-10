#ifndef _OR_H_
#define _OR_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Or : public AST {
   private:
    AST *lCond;
    AST *rCond;

   public:
    Or(AST *lCond, AST *rCond);
    AST *getLCond();
    AST *getRCond();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif