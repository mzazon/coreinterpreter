//
//  printer.h
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__printer__
#define __CSE3341__printer__

#include "parsetreeleaf.h"
#include "parsetree.h"

class Printer {
private:
	ParseTree* MyTree;
	int numSpaces;
public:
	Printer();
	void start(ParseTree* tree);
    void INCREASE_INDENT();
    void DECREASE_INDENT();
    void PRINT_WHITE_SPACE();
    void PROG();
	void DECL_SEQ();
	void STMT_SEQ();
	void DECL();
	void ID_LIST();
	void STMT();
	void ASSIGN();
	void INN();
	void IFF();
	void DOLOOP();
	void COND();
	void COMP();
	void COMP_OP();
	void EXPR();
	void TERM();
	void FACTOR();
	void CASE_STMT();
	void CASE_SEQ();
	void OUT();
	void IDD();
	void CONST();
    void CONST_LIST();

};

#endif /* defined(__CSE3341__printer__) */