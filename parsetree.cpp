//
//  parsetree.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/5/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "parsetree.h"

ParseTree::ParseTree()
{
    cursor = new ParseTreeLeaf();
    st = new SymbolTable();
}
bool ParseTree::SetChild1(ParseTreeLeaf* child)
{
    cursor->SetChild1(child);
    return true;
}

bool ParseTree::SetChild2(ParseTreeLeaf* child)
{
    cursor->SetChild2(child);
    return true;
}

bool ParseTree::SetChild3(ParseTreeLeaf* child)
{
    cursor->SetChild3(child);
    return true;
}

bool ParseTree::SetChild4(ParseTreeLeaf* child)
{
    cursor->SetChild4(child);
    return true;
}

bool ParseTree::SetChild5(ParseTreeLeaf* child)
{
    cursor->SetChild5(child);
    return true;
}

bool ParseTree::CursorTo1()
{
    cursor = cursor->GetChild1();
    return true;
}

bool ParseTree::CursorTo2()
{
    cursor = cursor->GetChild2();
    return true;
}

bool ParseTree::CursorTo3()
{
    cursor = cursor->GetChild3();
    return true;
}

bool ParseTree::CursorTo4()
{
    cursor = cursor->GetChild4();
    return true;
}

bool ParseTree::CursorTo5()
{
    cursor = cursor->GetChild5();
    return true;
}

bool ParseTree::setValue(std::string value)
{
    cursor->setValue(value);
    return true;
}

std::string ParseTree::getValue()
{
    return cursor->getValue();
}

bool ParseTree::setAlt(int alt)
{
    cursor->setAlt(alt);
    return true;
}

unsigned int ParseTree::getAlt()
{
    cursor->getAlt();
    return true;
}

unsigned int ParseTree::InsertSymbol(std::string s)
{
    return (*st).InsertSymbol(s);
}

std::string ParseTree::GetSymbol(unsigned int ID)
{
    return (*st).GetSymbolByIndex(ID);
}

unsigned int ParseTree::SymbolTableSize()
{
    return (*st).Size();
}

ParseTreeLeaf* ParseTree::Cursor()
{
    return cursor;
}

bool ParseTree::CursorToParent()
{
    cursor = (*cursor).GetParent();
    return true;
}