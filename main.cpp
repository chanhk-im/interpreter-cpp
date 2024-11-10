#include <iostream>

#include "Interpreter.h"
#include "Parser.h"
#include "ast/AST.h"
#include "ast/Add.h"
#include "ast/App.h"
#include "ast/Fun.h"
#include "ast/Id.h"
#include "ast/Num.h"
#include "ast/Sub.h"
#include "ast/With.h"

int main(int argc, char *argv[]) {
    string pOption, ConcreteCode;
    AST *ast;
    Parser parser;
    Interpreter interpreter;

    if (argc >= 3) {
        if (strcmp(argv[1], "-p") == 0) {
            pOption = argv[1];
            ConcreteCode = argv[2];
        } else
            return 0;
    } else if (argc == 2) {
        pOption = "Interprete";
        ConcreteCode = argv[1];
    }

    if (pOption == "-p") {
        string des = parser.desugar(ConcreteCode);
        ast = parser.parse(des);
        cout << des << '\n';
        cout << ast->getASTCode() << '\n';

        return 0;
    } else if (pOption == "Interprete") {
        string des = parser.desugar(ConcreteCode);
        ast = parser.parse(des);
        DefrdSub *mtSub = new DefrdSub();
        cout << interpreter.interprete(ast, mtSub)->getFaeValueCode() << '\n';
    } else
        cout << "Syntax Error.";

    return 0;
}