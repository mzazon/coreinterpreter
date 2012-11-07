//
//  symboltable.h
//  CSE3341
//
//  Created by Mike Zazon on 10/14/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__symboltable__
#define __CSE3341__symboltable__

#include <iostream>
#include <vector>

class Symbol {
private:
    std::string text;
    unsigned int index;
public:
    Symbol();
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

#endif /* defined(__CSE3341__symboltable__) */
