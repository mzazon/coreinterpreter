//
//  parsetree.h
//  CSE3341
//
//  Created by Mike Zazon on 10/5/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#ifndef __CSE3341__parsetree__
#define __CSE3341__parsetree__

#include <iostream>
#include "parsetreeleaf.h"
#include "symboltable.h"

class ParseTree {
private:
    ParseTreeLeaf * cursor;
    SymbolTable * st;
public:
    ParseTree();
    bool SetChild1(ParseTreeLeaf* child);
    bool SetChild2(ParseTreeLeaf* child);
    bool SetChild3(ParseTreeLeaf* child);
    bool SetChild4(ParseTreeLeaf* child);
    bool SetChild5(ParseTreeLeaf* child);
    bool CursorTo1();
    bool CursorTo2();
    bool CursorTo3();
    bool CursorTo4();
    bool CursorTo5();
    bool setValue(std::string value);
    std::string getValue();
    bool setAlt(int alt);
    unsigned int getAlt();
    unsigned int InsertSymbol(std::string s);
    std::string GetSymbol(unsigned int ID);
    unsigned int SymbolTableSize();
    ParseTreeLeaf* Cursor();
    bool CursorToParent();
};

#endif /* defined(__CSE3341__parsetree__) */
