//
//  parsetreenode.cpp
//  CSE3341
//
//  Created by Mike Zazon on 10/5/12.
//  Copyright (c) 2012 Mike Zazon. All rights reserved.
//

#include <iostream>
#include "parsetreeleaf.h"

ParseTreeLeaf::ParseTreeLeaf()
{

}

bool ParseTreeLeaf::setValue(std::string v)
{
    value = v;
    return true;
}

std::string ParseTreeLeaf::getValue()
{
    return value;
}

bool ParseTreeLeaf::setAlt(int a)
{
    alt = a;
    return true;
}

unsigned int ParseTreeLeaf::getAlt()
{
    return alt;
}

ParseTreeLeaf* ParseTreeLeaf::GetParent()
{
    return parent;
}

ParseTreeLeaf* ParseTreeLeaf::GetChild1()
{
    return child1;
}

ParseTreeLeaf* ParseTreeLeaf::GetChild2()
{
    return child2;
}

ParseTreeLeaf* ParseTreeLeaf::GetChild3()
{
    return child3;
}

ParseTreeLeaf* ParseTreeLeaf::GetChild4()
{
    return child4;
}

ParseTreeLeaf* ParseTreeLeaf::GetChild5()
{
    return child5;
}
bool ParseTreeLeaf::SetParent(ParseTreeLeaf* p)
{
    parent = p;
    return true;
}

bool ParseTreeLeaf::SetChild1(ParseTreeLeaf* c)
{
    child1 = c;
    (*child1).SetParent(this);
    return true;
}

bool ParseTreeLeaf::SetChild2(ParseTreeLeaf* c)
{
    child2 = c;
    (*child2).SetParent(this);
    return true;
}

bool ParseTreeLeaf::SetChild3(ParseTreeLeaf* c)
{
    child3 = c;
    (*child3).SetParent(this);
    return true;
}

bool ParseTreeLeaf::SetChild4(ParseTreeLeaf* c)
{
    child4 = c;
    (*child4).SetParent(this);
    return true;
}

bool ParseTreeLeaf::SetChild5(ParseTreeLeaf* c)
{
    child5 = c;
    (*child5).SetParent(this);
    return true;
}
