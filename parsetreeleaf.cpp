//
//  parsetreeleaf.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/4/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include "parsetreeleaf.h"

TokenEnum ParseTreeLeaf::getType()
{
    return type.token;
}

std::string ParseTreeLeaf::getID()
{
    return type.string;
}

int ParseTreeLeaf::getConst()
{
    return type.value;
}

int ParseTreeLeaf::getAlt()
{
    return Alt;
}

ParseTreeLeaf* ParseTreeLeaf::node1()
{
    return First;
}

ParseTreeLeaf* ParseTreeLeaf::node2()
{
    return Second;
}

ParseTreeLeaf* ParseTreeLeaf::node3()
{
    return Third;
}

ParseTreeLeaf* ParseTreeLeaf::rootnode()
{
    return Parent;
}

void ParseTreeLeaf::setToken(Token x)
{
    type = x;
}

void ParseTreeLeaf::setAlt(int x)
{
    Alt = x;
}

void ParseTreeLeaf::SetLeaf1(ParseTreeLeaf* x)
{
    First = x;
    x->Parent = this;
}

void ParseTreeLeaf::SetLeaf2(ParseTreeLeaf* x)
{
    Second = x;
    x->Parent = this;
}

void ParseTreeLeaf::SetLeaf3(ParseTreeLeaf* x)
{
    Third = x;
    x->Parent = this;
}
