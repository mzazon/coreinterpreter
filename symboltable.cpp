//
//  symboltable.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/14/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "symboltable.h"

SymbolTable::SymbolTable()
{
    table.push_back("init");
}

unsigned int SymbolTable::InsertSymbol(std::string s)
{
    table.push_back(s);
    size++;
    return size;
}

std::string SymbolTable::GetSymbolByIndex(unsigned int index)
{
    return table[index];
}

unsigned int SymbolTable::Size()
{
    return size;
}

bool SymbolTable::IsInTable(std::string s)
{
    for(int i=0; i<table.size(); i++)
    {
        if(table[i] == s)
        {
            return true;
        }
    }
    return false;
}