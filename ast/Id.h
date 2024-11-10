#ifndef _ID_H_
#define _ID_H_

#include <iostream>

#include "AST.h"

using namespace std;

class Id : public AST {
   private:
    string name;

   public:
    Id(string name);
    string getName();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif