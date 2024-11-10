#include "Parser.h"

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

AST *Parser::parse(string sexp) {
    vector<string> subExpressions = splitExpressionAsSubExpressions(sexp);

    if (subExpressions.size() == 1 && isNumeric(subExpressions.front())) {
        Num *num = new Num(subExpressions.front());
        return num;
    } else if (subExpressions.size() == 1 && !isNumeric(subExpressions.front())) {
        Id *id = new Id(subExpressions.front());
        return id;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "+") {
        Add *add = new Add(parse(subExpressions.at(1)), parse(subExpressions.at(2)));
        return add;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "-") {
        Sub *sub = new Sub(parse(subExpressions.at(1)), parse(subExpressions.at(2)));
        return sub;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "with") {
        vector<string> subWith = splitExpressionAsSubExpressions(subExpressions.at(1));
        Fun *fun = new Fun(subWith.at(0), parse(subExpressions.at(2)));
        App *app = new App(fun, parse(subWith.at(1)));
        return app;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "fun" && isList(subExpressions.at(1))) {
        vector<string> p = splitExpressionAsSubExpressions(subExpressions.at(1));
        if (p.size() == 1) {
            Fun *fun = new Fun(p.at(0), parse(subExpressions.at(2)));
            return fun;
        }
    } else if (subExpressions.size() == 2) {
        App *app = new App(parse(subExpressions.at(0)), parse(subExpressions.at(1)));
        return app;
    } else if (subExpressions.size() == 4 && subExpressions.front() == "if") {
        If *ifExpr = new If(parse(subExpressions.at(1)), parse(subExpressions.at(2)), parse(subExpressions.at(3)));
        return ifExpr;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "or") {
        Or *orExpr = new Or(parse(subExpressions.at(1)), parse(subExpressions.at(2)));
        return orExpr;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "=") {
        Eq *eq = new Eq(parse(subExpressions.at(1)), parse(subExpressions.at(2)));
        return eq;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "*") {
        Mult *mult = new Mult(parse(subExpressions.at(1)), parse(subExpressions.at(2)));
        return mult;
    }

    fputs("Bad syntax.", stderr);
    exit(0);
}

vector<string> Parser::splitExpressionAsSubExpressions(string sexp) {
    if ((sexp.front() == '{' && sexp.back() != '}') || (sexp.front() != '{' && sexp.back() == '}')) exit(0);

    if (sexp.front() == '{') sexp = sexp.substr(1, sexp.length() - 1);

    return getSubExpressions(sexp);
}

vector<string> Parser::getSubExpressions(string sexp) {
    vector<string> sexpressions = vector<string>();
    int openingParenthesisCount = 0;
    string strBuffer = "";
    for (int i = 0; i < sexp.length(); i++) {
        if (i == 0) {
            strBuffer = strBuffer + sexp.at(i);
            if (sexp.at(i) == '{') openingParenthesisCount++;
            continue;
        } else if (sexp.at(i) == ' ' && openingParenthesisCount == 0) {
            // buffer is ready to be a subexpression
            if (strBuffer.size() > 0) {
                sexpressions.push_back(strBuffer);
                strBuffer = "";  // Ready to start a new buffer
            }
            continue;
        } else {
            if (sexp.at(i) == '{' && openingParenthesisCount == 0) {
                openingParenthesisCount++;
                // Ready to start a new buffer
                strBuffer = "";
                strBuffer += sexp.at(i);
                continue;
            } else if (sexp.at(i) == '{') {
                openingParenthesisCount++;
                strBuffer = strBuffer + sexp.at(i);
                continue;
            } else if (sexp.at(i) == '}' && openingParenthesisCount > 0) {
                openingParenthesisCount--;
                strBuffer = strBuffer + sexp.at(i);
                continue;
            } else if (sexp.at(i) == '}') {
                // buffer is ready to be a subexpression
                sexpressions.push_back(strBuffer);
                continue;
            }
        }
        strBuffer = strBuffer + sexp.at(i);
    }

    if (sexp.back() != '}') sexpressions.push_back(strBuffer);

    return sexpressions;
}

bool Parser::isNumeric(string str) {
    regex pattern("-?\\d+(\\.\\d+)?");
    smatch match;
    return regex_match(str, match, pattern);
}

bool Parser::isList(string str) { return (str.front() == '{' && str.back() == '}'); }

bool Parser::isRecursion(string sexp) {
    vector<string> subExpressions = splitExpressionAsSubExpressions(sexp);

    if (subExpressions.size() == 1 && isNumeric(subExpressions.front())) {
        return false;
    } else if (subExpressions.size() == 1 && !isNumeric(subExpressions.front())) {
        return false;
    } else if (subExpressions.size() == 3 && subExpressions.front() == "+") {
        return isRecursion(subExpressions.at(1)) || isRecursion(subExpressions.at(2));
    } else if (subExpressions.size() == 3 && subExpressions.front() == "-") {
        return isRecursion(subExpressions.at(1)) || isRecursion(subExpressions.at(2));
    } else if (subExpressions.size() == 3 && subExpressions.front() == "with") {
        vector<string> subWith = splitExpressionAsSubExpressions(subExpressions.at(1));
        string idtf = subWith.at(0);
        string rec = subWith.at(1);
        vector<string> subRec = splitExpressionAsSubExpressions(rec);
        if (subRec.front() == "fun") {
            return rec.find(idtf) != string::npos;
        } else {
            return isRecursion(rec) || isRecursion(subExpressions.at(2));
        }
    } else if (subExpressions.size() == 3 && subExpressions.front() == "fun" && isList(subExpressions.at(1))) {
        return isRecursion(subExpressions.at(2));
    } else if (subExpressions.size() == 2) {
        return isRecursion(subExpressions.at(0)) || isRecursion(subExpressions.at(1));
    } else if (subExpressions.size() == 4 && subExpressions.front() == "if") {
        return isRecursion(subExpressions.at(1)) || isRecursion(subExpressions.at(2)) ||
               isRecursion(subExpressions.at(3));
    } else if (subExpressions.size() == 3 && subExpressions.front() == "or") {
        return isRecursion(subExpressions.at(1)) || isRecursion(subExpressions.at(2));
    } else if (subExpressions.size() == 3 && subExpressions.front() == "=") {
        return isRecursion(subExpressions.at(1)) || isRecursion(subExpressions.at(2));
    }

    return false;
}

string Parser::desugar(string sexp) {
    string str;
    vector<string> subExpressions = splitExpressionAsSubExpressions(sexp);
    if (!isRecursion(sexp)) return sexp;

    if (subExpressions.size() == 3 && subExpressions.front() == "+") {
        str += "{+ ";
        str += desugar(subExpressions.at(1));
        str += " ";
        str += desugar(subExpressions.at(2));
        str += "}";
    } else if (subExpressions.size() == 3 && subExpressions.front() == "-") {
        str += "{- ";
        str += desugar(subExpressions.at(1));
        str += " ";
        str += desugar(subExpressions.at(2));
        str += "}";
    } else if (subExpressions.size() == 3 && subExpressions.front() == "with") {
        vector<string> subWith = splitExpressionAsSubExpressions(subExpressions.at(1));
        string idtf = subWith.at(0);
        string rec = subWith.at(1);
        str +=
            "{with {mk-rec {fun {body-proc} {with {facX {fun {facY} {with {f {fun {x} {{facY facY} x}}} {body-proc "
            "f}}}} "
            "{facX facX}}}} ";
        str += "{with {";
        str += idtf;
        str += " {mk-rec {fun {";
        str += idtf;
        str += "} ";
        str += rec;
        str += "}}} ";
        str += subExpressions.at(2);
        str += "}}";
    } else if (subExpressions.size() == 3 && subExpressions.front() == "fun" && isList(subExpressions.at(1))) {
        str += "{fun ";
        str += desugar(subExpressions.at(1));
        str += " ";
        str += desugar(subExpressions.at(2));
        str += "}";
    } else if (subExpressions.size() == 2) {
        str += "{";
        str += desugar(subExpressions.at(0));
        str += " ";
        str += desugar(subExpressions.at(1));
        str += "}";
    } else if (subExpressions.size() == 4 && subExpressions.front() == "if") {
        str += "{if ";
        str += desugar(subExpressions.at(1));
        str += " ";
        str += desugar(subExpressions.at(2));
        str += " ";
        str += desugar(subExpressions.at(3));
        str += "}";
    } else if (subExpressions.size() == 3 && subExpressions.front() == "or") {
        str += "{or ";
        str += desugar(subExpressions.at(1));
        str += " ";
        str += desugar(subExpressions.at(2));
        str += "}";
    } else if (subExpressions.size() == 3 && subExpressions.front() == "=") {
        str += "{= ";
        str += desugar(subExpressions.at(1));
        str += " ";
        str += desugar(subExpressions.at(2));
        str += "}";
    }
    return str;
}