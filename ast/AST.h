#ifndef _AST_H_
#define _AST_H_

#include <iostream>

using namespace std;

typedef enum { NUL, NUM, ADD, SUB, WITH, ID, FUN, APP, IF, OR, EQ, MULT } typeNum;

/*
<RFAE> ::= <num>
        | {+ <RFAE> <RFAE>}
        | {- <RFAE> <RFAE>}
        | {* <RFAE> <RFAE>}
        | <id>
        | {fun {<id} <RFAE>}
        | {<RFAE> <RFAE>}
        | {if <RFAE> <RFAE> <RFAE>}
        | {or <RFAE> <RFAE>}
        | {= <RFAE> <RFAE>}
*/

class AST {
   private:
    typeNum type;

   public:
    virtual string getASTCode();
    virtual AST *copyAST();
    typeNum getType();
    void setType(typeNum to);
};

#endif