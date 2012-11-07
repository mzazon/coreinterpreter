//
//  executor.h
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__executor__
#define __CSE3341__executor__

#include "parsetreeleaf.h"
#include "scanner.h"
#include "tokenizer.h"
#include "parsetree.h"

class Executor {
private:
	Scanner* inputTokens;
	ParseTree* MyTree;
public:
	Executor();
    void setID(std::string x, int value);
	int get(std::string x);
    void ThrowExecutorError(std::string s);
    void PROG();
	void STMT_SEQ();
	void STMT();
	void ASSIGN();
    void start(ParseTree* tree, std::string inputFile);
	void INN();
    void OUT();
	void IFF();
	void DOLOOP();
	bool COND();
	bool COMP();
	TokenEnum COMP_OP();
	int EXPR();
	int TERM();
	int FACTOR();
	void CASE_STMT();
	int CASE_SEQ(std::string ID);
	std::string IDD();
    void ID_LIST(bool isUsedFor);
	int CONST();
    void CONST_LIST();
	bool SYMBOL_INIT_FLAG(std::string x);
	

};

#endif /* defined(__CSE3341__executor__) */
