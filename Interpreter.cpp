#include "Interpreter.h"

#include <iostream>
#include <regex>

#include "ast/Add.h"
#include "ast/App.h"
#include "ast/Eq.h"
#include "ast/Fun.h"
#include "ast/Id.h"
#include "ast/If.h"
#include "ast/Mult.h"
#include "ast/Num.h"
#include "ast/Or.h"
#include "ast/Sub.h"
#include "ast/With.h"

using namespace std;

// --------------RfaeValue--------------

FaeValue::FaeValue(int n) {
    type = NUM_V;
    this->n = n;
}
FaeValue::FaeValue(string param, AST *body, DefrdSub *ds) {
    type = CLO_V;
    this->param = param;
    this->body = body;
    this->ds = ds;
}
FaeValue::FaeValue(AST *expr, DefrdSub *ds, Box *value) {
    type = EXPR_V;
    this->expr = expr;
    this->ds = ds;
    this->value = value;
}
valueTypeNum FaeValue::getType() { return type; }
int FaeValue::getN() { return n; }
string FaeValue::getParam() { return param; }
AST *FaeValue::getBody() { return body; }
DefrdSub *FaeValue::getDs() { return ds; }
AST *FaeValue::getExpr() { return expr; }
Box *FaeValue::getValue() { return value; }
FaeValue *FaeValue::copyFaeValue() {
    FaeValue *newValue;
    if (type == NUM_V)
        newValue = new FaeValue(n);
    else
        newValue = new FaeValue(param, body->copyAST(), ds);
    return newValue;
}
string FaeValue::getFaeValueCode() {
    string code;
    if (type == NUM_V) {
        code += "(numV ";
        code += to_string(n);
        code += ")";
    } else if (type == CLO_V) {
        code += "(closureV ";
        code += param;
        code += " ";
        code += body->getASTCode();
        code += " ";
        code += ds->getDefrdSubCode();
        code += ")";
    } else if (type == EXPR_V) {
        code += "(exprV ";
        code += expr->getASTCode();
        code += " ";
        code += value->getBoxCode();
        code += " ";
        code += ds->getDefrdSubCode();
        code += ")";
    }
    return code;
}

// --------------DefrdSub--------------

DefrdSub::DefrdSub() { empty = true; }
DefrdSub::DefrdSub(string name, FaeValue *value, DefrdSub *ds) {
    empty = false;
    this->name = name;
    this->value = value;
    this->ds = ds;
}
bool DefrdSub::isEmpty() { return empty; }
string DefrdSub::getName() { return name; }
FaeValue *DefrdSub::getValue() { return value; }
DefrdSub *DefrdSub::getDs() { return ds; }
string DefrdSub::getDefrdSubCode() {
    string code;
    if (empty)
        code = "(mtSub)";
    else {
        code += "(aSub ";
        code += name;
        code += " ";
        code += value->getFaeValueCode();
        code += " ";
        code += ds->getDefrdSubCode();
        code += ")";
    }
    return code;
}

// --------------Box--------------
Box::Box(FaeValue *value) {
    this->value = value;
    empty = false;
}
Box::Box() {
    value = nullptr;
    empty = true;
}
FaeValue *Box::unBox() { return value; }
bool Box::getIsEmpty() { return empty; }
void Box::setBox(FaeValue *value) { this->value = value; }
Box *Box::copyBox() {
    if (value == nullptr) {
        return new Box();
    } else {
        return new Box(value);
    }
}
string Box::getBoxCode() {
    string code;
    if (empty) {
        code = "(box #f)";
    } else {
        code = "(box ";
        code += value->getFaeValueCode();
        code += ")";
    }
    return code;
}

// --------------Interpreter--------------

int Interpreter::stringToInteger(string strNum) {
    int resNum = 0;
    int negative = 1;

    if (strNum.front() == '-') {
        negative = -1;
        strNum = strNum.substr(1, strNum.length() - 1);
    }

    for (char num : strNum) {
        resNum *= 10;
        resNum += num - '0';
    }
    return resNum * negative;
}
FaeValue *Interpreter::interprete(AST *fae, DefrdSub *ds) {
    FaeValue *resultV;
    switch (fae->getType()) {
        case NUM: {
            int strNum;
            Num *num = (Num *)fae;
            strNum = stringToInteger(num->getNum());
            resultV = new FaeValue(strNum);
            break;
        }
        case ADD: {
            Add *add = (Add *)fae;
            AST *lhs = add->getLhs();
            AST *rhs = add->getRhs();
            FaeValue *interpL = interprete(lhs, ds);
            FaeValue *interpR = interprete(rhs, ds);
            if (interpL->getType() != NUM_V) {
                fputs("Syntax error!", stderr);
                exit(0);
            }
            resultV = new FaeValue(strict(interpL)->getN() + strict(interpR)->getN());
            break;
        }
        case SUB: {
            Sub *sub = (Sub *)fae;
            AST *lhs = sub->getLhs();
            AST *rhs = sub->getRhs();
            FaeValue *interpL = interprete(lhs, ds);
            FaeValue *interpR = interprete(rhs, ds);
            if (interpL->getType() != NUM_V) {
                fputs("Syntax error!", stderr);
                exit(0);
            }
            resultV = new FaeValue(strict(interpL)->getN() - strict(interpR)->getN());
            break;
        }
        case ID: {
            Id *id = (Id *)fae;
            return lookup(id->getName(), ds);
        }
        case FUN: {
            Fun *fun = (Fun *)fae;
            resultV = new FaeValue(fun->getParam(), fun->getBody(), ds);
            break;
        }
        case APP: {
            App *app = (App *)fae;

            FaeValue *fVal = strict(interprete(app->getFtn(), ds));
            FaeValue *aVal = new FaeValue(app->getArg(), ds, new Box());
            DefrdSub *newDs = new DefrdSub(fVal->getParam(), aVal, fVal->getDs());

            resultV = interprete(fVal->getBody(), newDs);
            break;
        }
        case IF: {
            If *ifExpr = (If *)fae;
            if (interprete(ifExpr->getCondExpr(), ds)->getN() >= 1) {
                resultV = interprete(ifExpr->getThenExpr(), ds);
            } else {
                resultV = interprete(ifExpr->getElseExpr(), ds);
            }
            break;
        }
        case OR: {
            Or *orExpr = (Or *)fae;
            if (interprete(orExpr->getLCond(), ds)->getN() == 1 || interprete(orExpr->getRCond(), ds)->getN() == 1)
                resultV = new FaeValue(1);
            else
                resultV = new FaeValue(0);
            break;
        }
        case MULT: {
            Mult *mult = (Mult *)fae;
            AST *lhs = mult->getLhs();
            AST *rhs = mult->getRhs();
            FaeValue *interpL = interprete(lhs, ds);
            FaeValue *interpR = interprete(rhs, ds);
            if (interpL->getType() != NUM_V) {
                fputs("Syntax error!", stderr);
                exit(0);
            }
            resultV = new FaeValue(interpL->getN() * interpR->getN());
            break;
        }
        case EQ: {
            Eq *eq = (Eq *)fae;
            FaeValue *leftV = interprete(eq->getLhs(), ds);
            FaeValue *rightV = interprete(eq->getRhs(), ds);

            if (leftV->getType() != NUM_V || rightV->getType() != NUM_V) {
                fputs("Syntax error!", stderr);
                exit(0);
            }

            if (leftV->getN() == rightV->getN())
                resultV = new FaeValue(1);
            else
                resultV = new FaeValue(0);
            break;
        }
        default:
            exit(0);
    }
    return resultV;
}
FaeValue *Interpreter::lookup(string name, DefrdSub *ds) {
    if (ds->isEmpty()) {
        fputs("free identifier", stderr);
        exit(0);
    }
    if (ds->getName().compare(name) == 0) return ds->getValue();
    return lookup(name, ds->getDs());
}
bool Interpreter::isNumeric(string str) {
    regex pattern("-?\\d+(\\.\\d+)?");
    smatch match;
    return regex_match(str, match, pattern);
}
FaeValue *Interpreter::strict(FaeValue *value) {
    if (value->getType() == EXPR_V) {
        Box *vBox = value->getValue();
        if (vBox->getIsEmpty()) {
            FaeValue *v = strict(interprete(value->getExpr(), value->getDs()));
            vBox->setBox(v);
            return v;
        } else {
            return vBox->unBox();
        }
    } else {
        return value;
    }
}