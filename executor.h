//
//  executor.h
//  CSE3341
//
//  Created by Mike Zazon on 10/17/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__executor__
#define __CSE3341__executor__

#include <iostream>
#include "scanner.h"
#include "parser.h"
#include "parsetreeleaf.h"
#include "parsetree.h"
#include "tokenizer.h"

class Executor {
private:
    ParseTree* tree;
    Scanner* input;
    bool isInit(std::string s);
    int getIDvalue(std::string s);
    void setIDvalue(std::string s, int value);

public:
    Executor(ParseTree* tree, std::string inputfile);
    void Start();
    void PROG();
    void STMT_SEQ();
    void ID_LIST(bool flag);
    void STMT();
    void ASSIGN();
    void IN();
    void IF();
    void LOOP();
bool COND();
    bool COMP();
    std::string COMP_OP();
int EXPR();
int TERM();
int FACTOR();
//void CASE();
//    int CASE_SEQ(std::string ID);
    // case stmt
void OUT();
std::string ID();
int CONST();

};

#endif /* defined(__CSE3341__executor__) */
