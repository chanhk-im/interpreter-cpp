#ifndef _NUM_H_
#define _NUM_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Num : public AST {
   private:
    string num = "0";

   public:
    Num(string num);
    string getNum();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif