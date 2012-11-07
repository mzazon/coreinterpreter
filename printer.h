//
//  printer.h
//  CSE3341
//
//  Created by Mike Zazon on 10/7/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__printer__
#define __CSE3341__printer__

#include <iostream>
#include "parsetree.h"
#include "parsetreeleaf.h"

class Printer {
private:
    ParseTree* t;
    int i;
public:
    Printer();
    Printer(ParseTree * tree);
    void PROG();
    void DECL_SEQ();
    void STMT_SEQ();
    void DECL();
    void STMT();
    void ID_LIST();
    void ASSIGN();
    void IF();
    void LOOP();
    void IN();
    void OUT();
    void EXPR();
    void COND();
    void CMPR();
    void CMPR_OP();
    void TERM();
    void FACTOR();
    void CASE();
    void CASE_LIST();
    void ID();
    void CONST();
    void INCREASE_INDENT();
    void DECREASE_INDENT();
    void Print(std::string s);
    void Space();
    void NewLine();
    
};

#endif /* defined(__CSE3341__printer__) */
