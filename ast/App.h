#ifndef _APP_H_
#define _APP_H_

#include <iostream>

#include "AST.h"

using namespace std;

class App : public AST {
   private:
    AST *ftn;
    AST *arg;

   public:
    App(AST *ftn, AST *arg);
    AST *getFtn();
    AST *getArg();
    string getASTCode() override;
    AST *copyAST() override;
};

#endif