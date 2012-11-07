//
//  main.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__parsetreeleaf__
#define __CSE3341__parsetreeleaf__

#include "tokenizer.h"

class ParseTreeLeaf {
public:
	TokenEnum getType();
	std::string getID();
	int getConst();
	int getAlt();
    void SetLeaf1(ParseTreeLeaf* x);
    ParseTreeLeaf* node1();
	void SetLeaf2(ParseTreeLeaf* x);
    ParseTreeLeaf* node2();
	void SetLeaf3(ParseTreeLeaf* x);
	ParseTreeLeaf* node3();
	ParseTreeLeaf* rootnode();
	void setToken(Token x);
	void setAlt(int x);

private:
	int Alt;
	Token type;
	ParseTreeLeaf* First;
	ParseTreeLeaf* Second;
	ParseTreeLeaf* Third;
	ParseTreeLeaf* Parent;

};


#endif /* defined(__CSE3341__parsetreeleaf__) */
