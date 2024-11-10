#ifndef _FUN_H_
#define _FUN_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Fun : public AST {
   private:
    string param;
    AST *body;

   public:
    Fun(string param, AST *body);
    string getParam();
    AST *getBody();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif