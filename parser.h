//
//  parser.h
//  CSE3341
//
//  Created by Mike Zazon on 10/15/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__parser__
#define __CSE3341__parser__

#include <iostream>
#include "parsetree.h"
#include "scanner.h"
#include "symboltable.h"

class Parser {
private:
    Scanner * scanner;
    SymbolTable * st;
    ParseTree * t;
    std::string token;
public:
    Parser(std::string filename);
    void Error(std::string s);
    ParseTree * PROG();
    ParseTree * DECL_SEQ();
    ParseTree * STMT_SEQ();
    ParseTree * DECL();
    ParseTree * STMT();
    ParseTree * ID_LIST();
    ParseTree * ASSIGN();
    ParseTree * IF();
    ParseTree * LOOP();
    ParseTree * IN();
    ParseTree * OUT();
    ParseTree * EXPR();
    ParseTree * COND();
    ParseTree * CMPR();
    ParseTree * CMPR_OP();
    ParseTree * TERM();
    ParseTree * FACTOR();
    ParseTree * CASE();
    ParseTree * CASE_LIST();
    ParseTree * ID();
    ParseTree * CONST();
    ParseTree * GetTree();
};


#endif /* defined(__CSE3341__parser__) */
