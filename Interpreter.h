#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <iostream>

#include "ast/AST.h"
#include "ast/Add.h"
#include "ast/Num.h"
#include "ast/Sub.h"

using namespace std;

typedef enum { NUM_V, CLO_V, EXPR_V } valueTypeNum;

class DefrdSub;
class Box;

class FaeValue {
   private:
    valueTypeNum type;

    // NumV
    int n;

    // ClosureV
    string param;
    AST *body;
    DefrdSub *ds;  // Closure & Expr

    // ExprV
    AST *expr;
    Box *value;

   public:
    FaeValue(int n);
    FaeValue(string param, AST *body, DefrdSub *ds);
    FaeValue(AST *expr, DefrdSub *ds, Box *value);
    valueTypeNum getType();
    int getN();
    string getParam();
    AST *getBody();
    DefrdSub *getDs();
    AST *getExpr();
    Box *getValue();
    FaeValue *copyFaeValue();
    string getFaeValueCode();
};

class DefrdSub {
   private:
    bool empty;
    string name;
    FaeValue *value;
    DefrdSub *ds;

   public:
    DefrdSub();
    DefrdSub(string name, FaeValue *value, DefrdSub *ds);
    bool isEmpty();
    string getName();
    FaeValue *getValue();
    DefrdSub *getDs();
    string getDefrdSubCode();
};

class Box {
   private:
    FaeValue *value;
    bool empty;

   public:
    Box(FaeValue *value);
    Box();
    FaeValue *unBox();
    bool getIsEmpty();
    void setBox(FaeValue *value);
    Box *copyBox();
    string getBoxCode();
};

class Interpreter {
   public:
    int stringToInteger(string strNum);
    FaeValue *interprete(AST *rfae, DefrdSub *ds);
    FaeValue *lookup(string name, DefrdSub *ds);
    bool isNumeric(string str);
    FaeValue *strict(FaeValue *value);
};

#endif