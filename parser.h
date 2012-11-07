//
//  parser.h
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__parser__
#define __CSE3341__parser__

#include "parsetree.h"
#include "parsetreeleaf.h"
#include "scanner.h"

class Parser {
public:
	Parser();
	ParseTree* start(std::string filename);
    ParseTree* PROG();
	ParseTree* DECL_SEQ();
	ParseTree* STMT_SEQ();
	ParseTree* DECL();
	ParseTree* STMT();
	ParseTree* ASSIGN();
	ParseTree* IN();
	ParseTree* IFF();
	ParseTree* DOWHILE();
	ParseTree* COND();
	ParseTree* COMP();
	ParseTree* COMP_OP();
	ParseTree* EXPR();
    ParseTree* CONST_LIST();
	ParseTree* TERM();
	ParseTree* FACTOR();
	ParseTree* CASE_SEQ();
    ParseTree* ID_LIST(bool in);
    ParseTree* ID_LIST_CHECK();
	ParseTree* CASE_STMT();
	ParseTree* OUT();
	ParseTree* ID_TERMINAL();
	ParseTree* CONST_TERMINAL();

private:
	void ThrowParserError();
	bool isin(std::string s);
	bool SYMBOL_INIT_FLAG(std::string s);
	void initializeID(std::string s);
	Scanner* parser;
	Symbol* symbolList;
	int numSymbols;
	int symbolIndex;
	ParseTree* tree;


};

#endif /* defined(__CSE3341__parser__) */