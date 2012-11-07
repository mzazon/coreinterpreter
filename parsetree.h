//
//  parsetree.h
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__parsetree__
#define __CSE3341__parsetree__

#include "tokenizer.h"
#include "parsetreeleaf.h"

class Symbol {
private:
    int id;
public:
    Symbol();
    bool SYMBOL_INIT_FLAG;
    std::string ID;
    int value;
};

class SymbolTable {
private:
    std::vector<std::string> table;
    unsigned int size;
public:
    SymbolTable();
    unsigned int InsertSymbol(std::string s);
    std::string GetSymbolByIndex(unsigned int index);
    unsigned int Size();
    bool IsInTable(std::string s);
};

class ParseTree {
private:
	ParseTreeLeaf* Leaf;
	Symbol* symbolList;
    SymbolTable ST;
	int numSymbols;
public:
	ParseTree();
	void SetLeaf1(ParseTreeLeaf* leaf);
	void SetLeaf2(ParseTreeLeaf* leaf);
	void SetLeaf3(ParseTreeLeaf* leaf);
	void setSymbolList(Symbol* x);
	void setNumSymbols(int x);
    bool first();
	bool second();
	bool third();
	bool root();
	Symbol* getSymbolList();
	int getNumSymbols();
	ParseTreeLeaf* getLeaf();
	TokenEnum getType();
    std::string getID();
    int getConst();
    int getAlt();
    void setToken(Token x);
    void setAlt(int x);

};

#endif /* defined(__CSE3341__parsetree__) */
