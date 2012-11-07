//
//  parsetree.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "parsetree.h"

//ParseTree Class functions

ParseTree::ParseTree()
{
    Leaf = new ParseTreeLeaf();
}

void ParseTree::SetLeaf1(ParseTreeLeaf* leaf)
{
    (*Leaf).SetLeaf1(leaf);
}

void ParseTree::SetLeaf2(ParseTreeLeaf* leaf)
{
    (*Leaf).SetLeaf2(leaf);
}

void ParseTree::SetLeaf3(ParseTreeLeaf* leaf)
{
    (*Leaf).SetLeaf3(leaf);
}

bool ParseTree::first()
{
    Leaf = (*Leaf).node1(); return true;
}

bool ParseTree::second()
{
    Leaf = (*Leaf).node2();return true;
}

bool ParseTree::third()
{
    Leaf = (*Leaf).node3();return true;
}

bool ParseTree::root()
{
    Leaf = (*Leaf).rootnode();return true;
}

void ParseTree::setSymbolList(Symbol* x)
{
    symbolList = x;
}

void ParseTree::setNumSymbols(int x)
{
    numSymbols = x;
}

Symbol* ParseTree::getSymbolList()
{
    return symbolList;
}

int ParseTree::getNumSymbols()
{
    return numSymbols;
}

ParseTreeLeaf* ParseTree::getLeaf()
{
    return Leaf;
}

TokenEnum ParseTree::getType()
{
    return (*Leaf).getType();
}

std::string ParseTree::getID()
{
    return (*Leaf).getID();
}

int ParseTree::getConst()
{
    return (*Leaf).getConst();
}

int ParseTree::getAlt()
{
    return (*Leaf).getAlt();
}

void ParseTree::setToken(Token x)
{
    (*Leaf).setToken(x);
}

void ParseTree::setAlt(int x)
{
    (*Leaf).setAlt(x);
}



// SymbolTable class functions

SymbolTable::SymbolTable()
{
    table.push_back("0init");
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

Symbol::Symbol()
{
    //default constructor
}